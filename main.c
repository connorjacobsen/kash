#include "include/kash.h"
#include "kash.tab.h"

pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;

void
print_env(void)
{
    char **env = environ;
    for (; *env; ++env)
    {
        printf("%s\n", *env);
    }
}

void
set_env(char *string)
{
    int success = putenv(string);
    if (success != 0) printf("Error: Could not successfully setenv!");
}

char
*get_pwd(void)
{
    return getenv("PWD");
}

void
waitfg(pid_t pid)
{
    while(current_fg_job_pid == pid) sleep(1);
}

/**
 * The kernel sends a SIGINT to the shell whenever the user
 * types ctrl-c at the keyboard. Catch it and send it along
 * to the foreground job.
 */
static void
handle_sigint(int sig)
{
    delete_job(first_job, current_fg_job_pid);
    kill(-current_fg_job_pid, sig);
}

/**
 * The kernel sends a SIGCHLD to the shell whenever a child job
 * terminates (becomes a zombie), or stops bc it received a SIGSTOP
 * or SIGTSTP signal. The handler reaps all available zombie children,
 * but doesn't wait for any other currently running children to
 * terminate.
 */
static void
handle_sigchld(int unused)
{
    pid_t pid = waitpid(-1, NULL, WNOHANG);
    if (pid <= 0) return;
    if (pid == current_fg_job_pid)
        current_fg_job_pid = -1;
    delete_job(first_job, pid);
}

/* initialize the shell. */
void
init_shell()
{
    /* See if we are running interactively */
    shell_terminal = STDIN_FILENO;
    shell_is_interactive = isatty(shell_terminal);

    if (shell_is_interactive)
    {
        /* Loop until we are in the foreground. */
        while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
            kill (- shell_pgid, SIGTTIN);

        /* Ignore interactive and job-control signal */
        // signal(SIGINT,  SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        // signal(SIGCHLD, SIG_IGN);
        install_signal_handler(SIGINT, handle_sigint);
        install_signal_handler(SIGCHLD, handle_sigchld);

        /* Put ourselves in our own process group. */
        shell_pgid = getpid();
        if (setpgid(shell_pgid, shell_pgid) < 0)
        {
            perror("Couldn't put the shell in its own process group");
            exit(1);
        }

        /* Grab control of the terminal */
        tcsetpgrp(shell_terminal, shell_pgid);

        /* Save default terminal attributes for shell */
        tcgetattr(shell_terminal, &shell_tmodes);
    }
}

void
kash_exec(command_list_t *list, char *stdin, outfile_t *stdout, char *stderr, int bg)
{
    unsigned int size = command_list_size(list);
    command_t **clist = command_list_to_array(list);

    if (list == NULL) return;
    FILE *in = NULL;
    FILE *out = NULL;
    FILE *err = NULL;
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;
    int fd_err = STDERR_FILENO;

    if (stdin != NULL) {
        in = fopen(stdin, "r");
        fd_in = fileno(in);
    }

    if (stdout != NULL) {
        if (stdout->append == 1)
            out = fopen(stdout->filename, "a+");
        else
            out = fopen(stdout->filename, "w+");
        fd_out = fileno(out);
    }

    if (stderr != NULL) {
        if (strcmp(stderr, "&1") == 0) {
            fd_err = fd_in;
        } else {
            err = fopen(stderr, "w+");
            fd_err = fileno(err);
        }
    }

    command_t *command = clist[0];

    /* we have a pipeline */
    int pipes[size * 2];
    /* create size*2 pipes */
    int i, j, k, status = 0, num_children = 0;
    int pfd_in, pfd_out;
    for (i = 0; i < size; ++i)
    {
        if (pipe(pipes+i*2) < 0)
        {
            perror("Couldn't create pipe!");
            return;
        }
    }

    #define CLOSE_ALL_PIPES \
        for (k = 0; k < size*2; k++) \
            if (pipes[k] != -1 && close(pipes[k]) == -1) \
                printf("couldn't close pipefd %d", pipes[k]);
    #define CLOSE_PREV_PIPE \
        if (pfd_out != -1 && close(pfd_out) == -1) \
            printf("couldn't close writing end with pipefd %d", pipes[k]); \
        else \
            pipes[j+1] = -1; // to indicate this side is closed

    /* loop through each command */
    for (i = 0, j = 0; i < size; ++i, j+=2, command = clist[i])
    {
        pfd_in  = (i > 0)? pipes[j-2] : -1;
        pfd_out = (i != (size-1))? pipes[j+1] : -1;
        
        if (is_built_in(command)) {
            handle_built_in(command);
        } else {
            num_children++;
            pid_t pid = fork();

            if(pid == 0) {
                if (pfd_in == -1)
                    dup2(fd_in, STDIN_FILENO);
                else
                    dup2(pfd_in, STDIN_FILENO);

                if (pfd_out == -1)
                    dup2(fd_out, STDOUT_FILENO);
                else
                    dup2(pfd_out, STDOUT_FILENO);

                dup2(fd_err, STDERR_FILENO);

                CLOSE_ALL_PIPES;
                char **args = prepend_command_to_args(command);
                if (execvp(args[0], args) < 0) {
                    printf("Couldn't execute command: %s\n", command->cmd);
                    exit(-1);
                }
            }
            CLOSE_PREV_PIPE;

            add_job(first_job, make_job(pid, command));

            /* handle background / foreground */
            if (bg) /* background */
                printf("[%d]\n", pid);
            else /* foreground */ {
                current_fg_job_pid = pid;
                waitfg(pid);
            }
        }
    }
    CLOSE_ALL_PIPES;
    int status_child = 0;
    for (k = 0; k < num_children; ++k)
        wait(&status_child);

    /* free fds for infile and outfile */
    if(fd_in != STDIN_FILENO) fclose(in);
    if(fd_out != STDOUT_FILENO) fclose(out);
}

void
print_welcome()
{
    FILE *fp = fopen("kash.txt", "r");
    char ch;
    assert(fp != NULL);
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
}

void
handle_built_in(command_t *command)
{
    if (strcmp("setenv", command->cmd) == 0) {
        print_command(command);
        if (command->numargs > 1)
            kash_setenv(command->args[0], command->args[1]);
        else {
            KERROR("setenv");
        }
    }
    if (strcmp("printenv", command->cmd) == 0) print_env();
    if (strcmp("unsetenv", command->cmd) == 0) {
        if (command->numargs == 1)
            unsetenv(command->args[0]);
        else
            KERROR("unsetenv");
    }
    if (strcmp("cd", command->cmd) == 0) change_dir(command);
    if (strcmp("alias", command->cmd) == 0) {
        if (command->numargs == 0) {
            print_aliases();
        } else if (command->numargs == 2) {
            alias(command->args[0], command->args[1]);
        } else {
            KERROR("alias");
        }
    }
    if (strcmp("unalias", command->cmd) == 0) {
        if (command->numargs == 1) {
            unalias(command->args[0]);
        } else
            KERROR("unalias");
    }
    if (strcmp("bye", command->cmd) == 0) exit(0);
    return;
}

void
change_dir(command_t *command)
{
    char *dir;
    if (command->numargs == 0) {
        dir = getenv("HOME");
    } else {
        dir = command->args[0];
    }
    int result = chdir(dir);
    if (result == 0)
        update_path(dir); // only update PWD on success
}

void
update_path(char *dir)
{
    char buffer[1024];
    getcwd(buffer, 1023);
    setenv("PWD", buffer, 1);
}

void
kash_setenv(char *var, char *value)
{
    setenv(var, value, 1);
}

outfile_t
*make_outfile(char *filename, int append)
{
    outfile_t *stdout = malloc(sizeof(outfile_t));
    assert(stdout != NULL);
    stdout->filename = strdup(filename);
    stdout->append = append;
    return stdout;
}

void
print_prompt(void)
{
    printf("%s%s%s: %s $ %s%s", KBOLD, KWHT, kPROMPT, get_pwd(), KNRM, KNOBOLD);
}

int
main(int argc, char* argv[])
{
    job_init();
    init_shell();
    print_welcome();
    initialize_alias_list();
    while(1) {
        print_prompt();
        int result = yyparse();
        printf("VALUE: %d\n", result);
        switch(result) {
            /* handle errors */
            case 0:
                break;
            case 1:
                printf("ERROR: Inavlid syntax, please check your syntax and try again.\n");
                break;
            case 2:
                printf("ERROR: Out of memory, please type `bye` to exit.\n");
                break;
            default:
                break;
        }
    }
    return 0;
}
