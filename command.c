#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "include/command.h"

command_t
*make_command(char *cmd, char **args, char *infile, char *outfile)
{
    printf("1\n");
    command_t *command = malloc(sizeof(command_t));
    command->cmd = strdup(cmd);
    printf("2\n");
    int arg_count = 0;
    char **argit = args;
    for (; *argit; ++argit)
    {
        ++arg_count;
    }
    printf("ARGCOUNT: %d\n", arg_count);
    command->args = malloc(arg_count * sizeof(char*)); // chars are 1 byte
    printf("3\n");
    int i = 0;
    for (; *args; ++args)
    {
        command->args[i] = strdup(*args);
        ++i;
    }
    command->numargs = i;
    printf("4\n");
    if (infile != NULL)
        command->infile = strdup(infile);

    if (outfile != NULL)
        command->outfile = strdup(outfile);
    printf("5\n");
    return command;
}

void
print_command(command_t *cmd)
{
    printf("Command: %s\n", cmd->cmd);
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
    printf("A\n");
    unsigned int size = arglist_size(arglist);
    printf("SIZE: %u\n", size);
    char **strings = malloc((sizeof(char*) * size) + 1);
    assert(strings != NULL); /* make sure we have enough memory */
    strings[size] = '\0'; /* assign null terminator */
    printf("B\n");
    /**
     * arglists are constructed so that the final element
     * points to NULL, signifying the end of the list.
     */
    int i = 0;
    if (size > 0) {
        printf("Hello!\n");
        while (arglist != NULL) {
            printf("WORLD!");
            if (arglist->head != NULL) {
                printf("To copy: %s\n", arglist->head->arg);
                strings[i] = strdup(arglist->head->arg);
                ++i;
            }
            arglist = arglist->tail;
        }
        printf("B2\n");
        char **str = strings;
        // for (; *str; ++str)
        // {
        //     printf("STR: %s\n", *str);
        // }
        while (size-- > 0)
        {
            printf("STR: %s\n", *str);
            ++str;
        }
    }    
    printf("C\n");
    return strings;
}
