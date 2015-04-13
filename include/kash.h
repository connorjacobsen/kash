#ifndef KASH_H_
#define KASH_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "constants.h"
#include "command.h"
#include "alias.h"
#include "job.h"
#include "ksignal.h"
#include "variables.h"
#include "wildcard.h"

/* may not be declared in unistd.h */
extern char** environ;

extern int linenum;
extern int charnum;

#define KERROR(f) printf("Wrong number of args to command: %s, at %d:%d\n", f, linenum, charnum)

typedef struct outfile_t {
    char *filename;
    int append;
} outfile_t;

outfile_t
*make_outfile(char *filename, int append);

void
print_prompt(void);

void
waitfg(pid_t pid);

/**
 * Prints all environment variables.
 *
 * uses `extern char** environ` from unistd.h
 */
void print_env(void);

void set_env(char *string);

/* get the current PWD environ variable */
char* get_pwd(void);

/* initializes the shell */
void init_shell(void);

void
print_welcome();

/* execute a non built-in method */
void
kash_exec(command_list_t *list, char *stdin, outfile_t *stdout, char *stderr, int bg);

/**
 * Built in command handlers.
 */
void
handle_built_in(command_t *command);

void
change_dir(command_t *command);

/**
 * The PWD environment variable needs to be correctly set
 * after we change the working directory with change_dir.
 */
void
update_path(char *dir);

/**
 * Sets the variable @var in the environ to be @value.
 *
 * Named in such a way to avoid conflict with the unix
 * built-in function setenv()
 */
void
kash_setenv(char *var, char *value);

#endif /* KASH_H_ */