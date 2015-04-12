#ifndef UTIL_H_
#define UTIL_H_

unsigned int
str_array_size(char **str_arr);

/**
 * Splits a given string @str into a NULL-terminated array of 
 * strings delimited by the space character.
 *
 * Returns pointer to pointers to char.
 */
char
**split_string(char *str);

/**
 * Concatenates two NULL-terminated arrays of strings into a 
 * single NULL-terminated array of strings.
 *
 * Returns pointer to pointers to char.
 */
char
**concat_string_arrays(char **s1, int size1, char **s2, int size2);

#endif /* UTIL_H_ */