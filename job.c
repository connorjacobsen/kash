#include "stdlib.h"
#include "string.h"
#include "include/job.h"

// void
// job_init(void)
// {
//     job_t *first_job = NULL;
//     int next_jid = 1;
// }

job_t
*make_job(pid_t pgid, const char *command)
{
    job_t *job = malloc(sizeof(job_t));
    job->jid = next_jid++;
    job->command = strdup(command);
    return job;
}
