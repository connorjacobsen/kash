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
#include "process.h"

/* may not be declared in unistd.h */
extern char** environ;

/**
 * Prints all environment variables.
 *
 * uses `extern char** environ` from unistd.h
 */
void print_env(void);

void set_env(char *string);

/**
 * Redirect stderr to stdout (so that driver will get all output
 * on the pipe connected to stdout)
 */
static void merge_file_descriptors(void);

/* get the current PWD environ variable */
char* get_pwd(void);

/* initializes the shell */
void init_shell(void);

void
print_welcome();

/* launch a new process */
void launch_process(process_t *p, pid_t pgid, int infile,
                    int outfile, int errfile, int foreground);

/* launch a new job */
void launch_job(job_t *job, int foreground);

/* execute a non built-in method */
void
kash_exec(command_t *command);

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
 *
 * if @dir == ".", we do NOT update PWD.
 * if @dir == "..", we need to remove the last '/' from the path.
 * otherwise, we need to set PWD to HOME + @dir.
 */
void
update_path(char *dir);

#endif /* KASH_H_ */