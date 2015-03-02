#include "include/element.h"

/* Creates a new element_t object */
element_t* element_new_element(char* k, char* v)
{
    /**
     * allocates space for the element_t object, which should be
     * pointer_size * 2, since we are allocated space for the 
     * pointers to key and value, not the objects themselves.
     */
    element_t* el = malloc(sizeof(element_t));
    el->key = malloc(sizeof(k));
    el->key = k;
    el->value = malloc(sizeof(v));
    el->value = v;
    return el;
}
