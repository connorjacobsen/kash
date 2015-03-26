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

int
main(int argc, char* argv[])
{
    initialize_alias_list();
    job_init();
    yyparse();
    return 0;
}
