/**
 * Maps char* to char*.
 *
 * May be extended to support other data types for values, but was
 * not necessary for this implementation.
 */
#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>
#include "element.h"

typedef struct map {
    element_t elements[25];
    unsigned int size;
    unsigned int capacity;
} map_t;

map_t* make_map(void);
size_t map_size(map_t* map);

#endif /* MAP_H_ */