/**
 * Maps char* to char*.
 *
 * May be extended to support other data types for values, but was
 * not necessary for this implementation.
 *
 * Current implementation runs in O(n) time. Could be updated to use
 * O(1) time with a hashing function if needed for huge data sets.
 * However, since primary use-case is for storing ENV variables,
 * O(n) time should be efficient enough.
 */
#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>
#include "element.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct map {
    element_t* elements;
    unsigned int size;
    unsigned int capacity;
} map_t;

map_t* make_map(void);
size_t map_size(map_t* map);
int    map_contains(map_t* m, char* key);
char  *map_get(map_t* m, char* key);
void   map_put(map_t* m, char* k, char* v);
void   map_del(map_t* m, char* key);

#endif /* MAP_H_ */