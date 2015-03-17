#ifndef PROCESS_H_
#define PROCESS_H_

/**
 * A process is a single process.
 */
typedef struct process_t {
    struct process_t *next;     /* next process in pipeline */
    char **argv;                /* for exec */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
} process_t;

#endif /* PROCESS_H_ */