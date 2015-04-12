#include "include/variables.h"

int
contains_env_variable(char *str)
{
    int found = 0;
    while (*str) {
        if (*str == '$' && *(str+1) == '{' && strchr(str, '}') != NULL) {
            found = 1;
            break;
        }
        ++str;
    }
    return found;
}

char
*get_env_variable_key(char *str)
{
    char key[1024];
    int index = 0;
    int found = 0;
    while (*str) {
        if (found) { /* we are in the variable string */
            if (*str == '}') {
                /* end of the variable found */
                key[index] = 0;
                return strdup(key);
            } else {
                key[index++] = *str;
            }
        } else { /* havent found the variable string */
            if (*str == '$' && *(str+1) == '{') {
                found = 1;
                ++str; /* move the pointer over an extra space */
            }
        }
        ++str;
    }
}

int
new_string_size(char *str, char *key, char *value)
{
    int ls = strlen(str);
    int lkey = strlen(key) + 3;
    int lvalue = strlen(value);
    return ls - lkey + lvalue;
}

int
index_of_env_variable(char *str)
{
    int index = 0;
    while (*str) {
        if (*str == '$' && *(str+1) == '{') {
            return index;
        }
        ++index;
        ++str;
    }
    return -1; /* error */
}

char
*build_new_string(char *str, char *key, char *value)
{
    int index = 0;
    int str_size = new_string_size(str, key, value);
    char new_str[str_size+1];
    int start_of_var = index_of_env_variable(str);
    if (start_of_var == -1) return str; /* error */
    for (; index < start_of_var; ++index)
        new_str[index] = str[index];

    int original_str_index = index + 3; /* save for later */
    /* the extra 3 for the ${} chars around the key */

    int i;
    for(i = 0; i < strlen(value); ++i, ++index)
        new_str[index] = value[i];

    original_str_index += strlen(key);
    for (; original_str_index < strlen(str); ++original_str_index, ++index)
        new_str[index] = str[original_str_index];

    new_str[str_size] = 0;
    return new_str;
}

char
*insert_env_variable(char *str)
{
    if (contains_env_variable(str)) {
        char *key = get_env_variable_key(str);
        char *value = getenv(key);
        if (value != NULL) {
            /* insert value in place of key */
            char *nstr = build_new_string(str, key, value);
            return nstr;
        } else {
            /* insert empty string in place of key */
            return str; // build_new_string(str, key, "");
        }
    } else {
        return str;
    }
}
