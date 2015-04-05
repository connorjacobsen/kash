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

static void
merge_file_descriptors(void)
{
    dup2(STDOUT_FILENO, STDERR_FILENO);
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
        signal(SIGINT,  SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);

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
kash_exec(command_t *command)
{
    // printf("BUILT IN: %d\n", is_built_in(command));
    FILE *in = NULL;
    FILE *out = NULL;
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;

    if(command->infile != NULL){
        in = fopen(command->infile, "r");
        fd_in = fileno(in);
    }

    if(command->outfile != NULL){
        out = fopen(command->outfile, "w+");
        fd_out = fileno(out);
    }

    if (is_built_in(command)) {
        /* handle built in here */
    } else {
        pid_t pid = fork();

        if(pid == 0) {
            setpgid(0, 0); // Group processes
            // Execute the command
            if(fd_in != STDIN_FILENO){
                // Redirect standard input and err to file's descriptor
                dup2(fd_in, STDIN_FILENO);
                dup2(fd_in, STDERR_FILENO);
            }
            if(fd_out != STDOUT_FILENO){
                dup2(fd_out, STDOUT_FILENO);
            }
            char **args = prepend_command_to_args(command);
            int result = execvp(args[0], args);
        }

        // add a job to the job list

        // do check for background vs. foreground.
    }
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

int
main(int argc, char* argv[])
{
    init_shell();
    print_welcome();
    merge_file_descriptors();
    initialize_alias_list();
    //job_init();
    printf("%s", kPROMPT);
    yyparse();
    return 0;
}
