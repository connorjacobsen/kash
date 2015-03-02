#ifndef ELEMENT_H_
#define ELEMENT_H_
#include <stdio.h>
#include <stdlib.h>

/**
 * A Map of string keys to string values.
 */
typedef struct element {
    char* key;
    char* value;
} element_t;

/* Create a new element_t object */
element_t* make_element(char* k, char* v);

#endif /* ELEMENT_H_ */
