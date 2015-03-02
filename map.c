#include "include/map.h"

/**
 * make_map
 *
 * Creates a new map_t object in the heap and returns a pointer
 * to it.
 *
 * @params void
 * @return pointer to a map_t
 */
map_t* make_map(void)
{
    map_t* m = malloc(sizeof(map_t));
    m->size = 0;
    m->capacity = 25;
    return m;
}

/**
 * map_size
 *
 * Returns the size of the map (number of elements).
 *
 * @params m -- map_t* object of which to get the size.
 * @return size_t size of the map_t.
 */
size_t map_size(map_t* m)
{
    return m->size;
}