#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Determines whether or not a string contains the ${ }
 * pattern that demarcates an environment variable.
 */
int
contains_env_variable(char *str);

/**
 * Pulls the ${ENV} key from a given string.
 *
 * Assumes the string contains and environment variable.
 */
char
*get_env_variable_key(char *str);

int
new_string_size(char *str, char *key, char *value);

int
index_of_env_variable(char *str);

char
*build_new_string(char *str, char *key, char *value);

/**
 * Searches the given cstring for an environment variable, if one is found
 * then it replaces the variable with its value and returns the updated string.
 *
 * If no environment variable is found, just returns the original string.
 *
 * If an environment variable is found, but does not resolve to a value, the empty
 * string is inserted in its place. 
 */
char
*insert_env_variable(char *str);

#endif /* VARIABLES_H_ */