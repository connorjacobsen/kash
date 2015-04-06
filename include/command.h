#ifndef COMMAND_H_
#define COMMAND_H_

typedef struct command_t {
    char *cmd;      /* name of the command */
    char **args;    /* array of arguments to the command */
    int  numargs;
} command_t;

typedef struct command_list_t {
    struct command_t *head;
    struct command_list_t *tail;
} command_list_t;

typedef struct arg_t {
    char *arg;
} arg_t;

typedef struct arglist_t {
    struct arg_t *head;
    struct arglist_t *tail;
} arglist_t;

command_t 
*make_command(char *cmd, char **args);

/* Prints a command, useful for debugging. */
void
print_command(command_t *cmd);

void
print_command_args(command_t *cmd);

/**
 * Returns 0 if the command is not a built in command,
 * returns 1 if it IS a built in command.
 */
int
is_built_in(command_t *command);

/**
 * Creates a new command_list_t object and returns a pointer to it.
 */
command_list_t
*make_command_list(command_t *head, command_list_t *tail);

/**
 * Returns the size of the command_list_t.
 */
unsigned int
command_list_size(command_list_t *list);

/**
 * The cons-cell style list is easy to build in the parser, but
 * it is not as convenient to operate on as an array. This method
 * returns a nice array that we can operate on the pipe_commmands_t
 * more easily.
 *
 * The end of the list is marked by a NULL pointer.
 */
command_t
**command_list_to_array(command_list_t *list);

/**
 * Executes a set of pipelined commands.
 */
void
execute_command_list(command_list_t *list);

/**
 * Creates a new char* array to send to execvp() call.
 */
char
**prepend_command_to_args(command_t *command);

arg_t
*make_arg(char *arg);

void
arglist_print(arglist_t *arglist);

unsigned int
arglist_size(arglist_t *arglist);

char
**arglist_to_strings(arglist_t *arglist);

/**
 * Concatenates an arg_t with an existing arglist_t.
 *
 * This creates a recursive data structure that will allow us to
 * create a NULL terminated list.
 */
arglist_t
*make_arglist(arg_t *arg, arglist_t *arglist);

#endif /* COMMAND_H_ */