#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "include/util.h"

unsigned int
str_array_size(char **str_arr)
{
    unsigned int count = 0;
    int i;
    for (i = 0; str_arr[i] != NULL; i++)
        ++count;
    return count;
}

char
**split_string(char *str)
{
    size_t char_size = strlen(str) + 1;
    char s[char_size]; 
    strncpy(s, str, char_size);
    s[char_size] = '\0';
    char *p;

    int count = 0;
    int i;
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == ' ') count++;
    count += 2;

    char **list = malloc(sizeof(char*) + 1);
    assert(list != NULL);

    p = strtok (s, " ");

    i = 0;
    while (p != NULL)
    {
        list[i++] = p;
        p = strtok (NULL, " ");
    }
    list[i] = NULL;
    return list;
}

char
**concat_string_arrays(char **s1, int size1, char **s2, int size2)
{
    char** result = malloc(sizeof(char) * 10);

    return result;
}