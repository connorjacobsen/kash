#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "include/command.h"

command_t
*make_command(char *cmd, char **args)
{
    command_t *command = malloc(sizeof(command_t));
    command->cmd = strdup(cmd);
    int arg_count = 0;
    char **argit = args;
    for (; *argit; ++argit)
    {
        ++arg_count;
    }
    command->args = malloc(arg_count * sizeof(char*)); // chars are 1 byte
    int i = 0;
    int j = arg_count-1;
    for (; *args; ++args)
    {
        command->args[j--] = strdup(*args);
        ++i;
    }
    command->numargs = i;
    return command;
}

void
print_command(command_t *cmd)
{
    printf("Command: '%s'\n", cmd->cmd);
    printf("Args:\n");
    print_command_args(cmd);
}

void
print_command_args(command_t *cmd)
{
    char **args = cmd->args;
    int i = cmd->numargs-1;
    int j = 0;
    for (; i >= 0; --i)
    {
        printf("%d: ", j++);
        printf("%s\n", args[i]);
    }

}

int
is_built_in(command_t* command)
{
    if (strcmp("setenv", command->cmd) == 0) return 1;
    if (strcmp("printenv", command->cmd) == 0) return 1;
    if (strcmp("unsetenv", command->cmd) == 0) return 1;
    if (strcmp("cd", command->cmd) == 0) return 1;
    if (strcmp("alias", command->cmd) == 0) return 1;
    if (strcmp("unalias", command->cmd) == 0) return 1;
    if (strcmp("bye", command->cmd) == 0) return 1;
    return 0;
}

command_list_t
*make_command_list(command_t *head, command_list_t *tail)
{
    command_list_t *list = malloc(sizeof(command_list_t));
    assert(list != NULL); /* memory check */
    list->head = head;
    list->tail = tail;
    return list;
}

unsigned int
command_list_size(command_list_t *list)
{
    unsigned int size = 0;
    while (list != NULL) {
        if (list->head != NULL) ++size;
        list = list->tail;
    }
    return size;
}

/* still needs to be tested */
command_t
**command_list_to_array(command_list_t *list)
{
    unsigned int size = command_list_size(list);
    command_t **clist = malloc(sizeof(command_t*));
    assert(clist != NULL);
    clist[size--] = NULL;
    while (list != NULL)
    {
        if (list->head != NULL)
        {
            clist[size--] = list->head;
        }
        list = list->tail;
    }
    return clist;
}

char
**prepend_command_to_args(command_t *command)
{
    /* +1 for the NULL pointer, and +1 for the command name. */
    char **exec_args = malloc(command->numargs * sizeof(char*) + 2);
    exec_args[command->numargs + 1] = NULL;
    exec_args[0] = command->cmd; // command goes at head of list
    int i;
    for (i = 0; i < command->numargs; ++i)
        exec_args[i+1] = command->args[i];
    return exec_args;
}

arg_t
*make_arg(char *arg)
{
    arg_t *a = malloc(sizeof(arg_t));
    assert(a != NULL); /* make sure we have enough memory */
    a->arg = strdup(arg);
    return a;
}

arglist_t
*make_arglist(arg_t *arg, arglist_t *arglist)
{
    arglist_t *new_arglist = malloc(sizeof(arglist_t));
    assert(new_arglist != NULL); /* make sure we have enough memory */
    new_arglist->head = arg;
    new_arglist->tail = arglist;
    return new_arglist;
}

unsigned int
arglist_size(arglist_t *arglist)
{
    unsigned int size = 0;
    while (arglist != NULL) {
        if (arglist->head != NULL) ++size;
        arglist = arglist->tail;
    }
    return size;
}

void
arglist_print(arglist_t *arglist)
{
    do {
        if (arglist->head != NULL) {

        }
    } while (arglist->tail != NULL);
}

char
**arglist_to_strings(arglist_t *arglist)
{
    assert(arglist != NULL);
    unsigned int size = arglist_size(arglist);
    char **strings = malloc((sizeof(char*) * size) + 1);
    assert(strings != NULL); /* make sure we have enough memory */
    strings[size] = NULL; /* assign null terminator */
    /**
     * arglists are constructed so that the final element
     * points to NULL, signifying the end of the list.
     */
    int i = 0;
    if (size > 0) {
        while (arglist != NULL) {
            if (arglist->head != NULL) {
                strings[i] = strdup(arglist->head->arg);
                ++i;
            }
            arglist = arglist->tail;
        }
        char **str = strings;
        // for (; *str; ++str)
        // {
        //     printf("STR: %s\n", *str);
        // }
        while (size-- > 0)
        {
            ++str;
        }
    }    
    return strings;
}
