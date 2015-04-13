#ifndef JOB_H_
#define JOB_H_

#include <sys/types.h> /* need pid_t */
#include "command.h"
#include "process.h"

/**
 * A job is a pipeline of processes.
 *
 * struct job_t manages all the information about a currently
 * executing job.
 */
typedef struct job_t {
    int jid;                    /* the job ID */
    struct job_t *next;         /* next active job */
    command_t *command;           /* command line, used for messages */
    pid_t pgid;                 /* process group ID */
} job_t;

/* The active jobs are linked into a list. This is its head. */
job_t *first_job; /* = NULL; */

/* The jid to assign to the next created job. */
int next_jid;

pid_t current_fg_job_pid;

/* initializes the values of first_job to NULL, and next_jid to 1 */
void
job_init(void);

/* Initializes a new job_t object. */
job_t
*make_job(pid_t pgid, command_t *command);

/**
 * Adds a job to the provided job list.
 */
void
add_job(job_t *job_list, job_t *job);

/* Find the active job with the indicated pgid. */
job_t
*find_job (pid_t pgid);

/**
 * Return 1 if the job with the provided pgid was successfully removed.
 * If the job was not successfully removed or the pgid was bad, it will
 * fail and return 0.
 */
int
delete_job(job_t *job_list, pid_t pgid);

/* Return 1 if all processes in the job have stopped or completed. */
// int job_is_stopped (job_t *job);

/* Return 1 if all processes in the job have completed. */
// int job_is_completed (job_t *job);

/* Return 1 if all jobs are successfully removed from the job_list */
int clear_job_list(job_t *job_list);

/* Return the pgid of the current foreground job, or 0 if no such job. */
pid_t current_foreground_job(job_t* job_list);

/* Return the jid associated with the given pgid, or 0 if no such pgid. */
// int jid_from_pgid(pid_t pgid);

#endif /* JOB_H_ */