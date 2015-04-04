#ifndef JOB_H_
#define JOB_H_

#include <sys/types.h> /* need pid_t */
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
    char *command;              /* command line, used for messages */
    process_t *first_process;   /* list of processes in this job */
    pid_t pgid;                 /* process group ID */
    int stdin, stdout, stderr;  /* standard i/o channels */
} job_t;

/* The active jobs are linked into a list. This is its head. */
extern job_t *first_job; /* = NULL; */

/* The jid to assign to the next created job. */
static int next_jid  = 1;

/* initializes the values of first_job to NULL, and next_jid to 1 */
void job_init(void);

/* Initializes a new job_t object. */
job_t *make_job(pid_t pgid, const char *command);

/**
 * Adds a job to the provided job list.
 * Return 1 if the job was successfully added to the jobs list.
 */
int add_job(job_t *job_list, job_t *job);

/* Find the active job with the indicated pgid. */
job_t *find_job (pid_t pgid);

/**
 * Return 1 if the job with the provided pgid was successfully removed.
 * If the job was not successfully removed or the pgid was bad, it will
 * fail and return 0.
 */
int delete_job(job_t *job_list, pid_t pgid);

/* Return 1 if all processes in the job have stopped or completed. */
int job_is_stopped (job_t *job);

/* Return 1 if all processes in the job have completed. */
int job_is_completed (job_t *job);

/* Return 1 if all jobs are successfully removed from the job_list */
int clear_job_list(job_t *job_list);

/* Return the pgid of the current foreground job, or 0 if no such job. */
pid_t current_foreground_job(job_t* job_list);

/* Return the jid associated with the given pgid, or 0 if no such pgid. */
int jid_from_pgid(pid_t pgid);

#endif /* JOB_H_ */