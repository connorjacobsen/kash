#ifndef KASH_H_
#define KASH_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include "constants.h"
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

/* launch a new process */
void launch_process(process_t *p, pid_t pgid, int infile,
                    int outfile, int errfile, int foreground);

/* launch a new job */
void launch_job(job_t *job, int foreground);

/* execute a non built-in method */
static void kash_exec(char* command_line);

#endif /* KASH_H_ */