#include "stdlib.h"
#include "string.h"
#include "include/job.h"

void
job_init(void)
{
    first_job = NULL;
    current_fg_job_pid = (pid_t)-1;
    next_jid = 1;
}

job_t
*make_job(pid_t pgid, command_t *command)
{
    job_t *job = malloc(sizeof(job_t));
    job->jid = next_jid++;
    job->command = command;
    job->next = NULL;
    return job;
}

void
add_job(job_t *job_list, job_t *job)
{
    if (job_list == NULL)
        job_list = job;
    else {
        while (job_list->next != NULL) {
            if (job_list != NULL)
                job_list = job_list->next;
            else
                break;
        }
        job_list->next = job;
    }
}

int
delete_job(job_t *job_list, pid_t pgid)
{
    job_t *head = job_list;
    job_t *prev = head;
    if (head != NULL) {
        while (head->next != NULL) {
            if (head != NULL) {
                if (head->pgid == pgid) {
                    /* delete this job */
                    if (head == job_list) {
                        /* we are at the head of the list */
                        job_list = job_list->next;
                        free(head);
                        return 1;
                    } else {
                        prev->next = head->next;
                        free(head);
                        return 1;
                    }
                }
                prev = head;
                head = head->next;
            }
        }
        return 0;
    } else {
        return 0;
    }
}

int
clear_job_list(job_t *job_list)
{
    job_t *head = job_list;
    job_list = NULL;
    while (head->next != NULL) {
        if (head != NULL) {
            job_t *tmp = head;
            head = head->next;
            free(tmp);
        } else
            break;
    }
    return 1;
}

pid_t
current_foreground_job(job_t* job_list)
{

}
