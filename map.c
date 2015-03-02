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
    m->elements = malloc(sizeof(element_t) * 25);
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

/**
 * Reallocates the memory space for the map's elements.
 *
 * Doubles element space when called.
 */
void realloc_map_elements(map_t* m)
{
    int i;
    int new_capacity = m->capacity * 2;

    /* array of new_capacity element_t's */
    /* may want to consider reporting an error on failure */
    element_t* els = malloc(sizeof(element_t) * new_capacity);

    /* copy over data */
    for (i = 0; i < m->size; i++) {
        els[i] = m->elements[i];
    }

    /* free old memory */
    free(m->elements);
    /* probably not necessary, but used for safety */
    m->elements = NULL;

    /* set new storage */
    m->elements = els;
    m->capacity = new_capacity;
}

/**
 * Sets an the given key @k to the given value @v for a map_t* @m.
 *
 * O(n) insertion.
 *
 * @param m -- map_t* map on which to perform the put action.
 * @param k -- char* key to be set.
 * @param v -- char* value to be set.
 * @return void.
 */
void map_put(map_t* m, char* k, char* v)
{
    element_t* el = make_element(k, v);

    /* reallocate elements array if necessary */
    if (m->size == m->capacity)
        realloc_map_elements(m);

    m->elements[m->size++] = *el;
}

/**
 * Returns the value of @key if it exists in @m, NULL otherwise.
 *
 * @param m -- map_t* map to search.
 * @param key -- char* key for which to search.
 * @return char* value for @key in @m if exists, NULL otherwise.
 */
char* map_get(map_t* m, char* key)
{
    int i;
    for (i = 0; i < m->size; i++) {
        if (m->elements[i].key == key)
            return m->elements[i].value;
    }
    return NULL;
}

/**
 * Boolean function which determines the existence of a key in a given map.
 *
 * @param m -- map_t* map to search.
 * @param key -- char* key for which to search.
 * @return 1 if @key is in @m, 0 otherwise.
 */
int map_contains(map_t* m, char* key)
{
    int i;
    for (i = 0; i < m->size; i++) {
        if (m->elements[i].key == key)
            return 1;
    }
    return 0;
}

/**
 * Deletes the key-value pair with key @key from @m if exists.
 *
 * @param m -- map_t map to search.
 * @param key -- char* key for which to search.
 * @return void.
 */
void map_del(map_t* m, char* key)
{
    int i;
    for (i = 0; i < m->size; i++) {
        if (m->elements[i].key == key) {
            /* set match equal to value at end of array */
            m->elements[i] = m->elements[(m->size - 1)];
            /* decrement size to effectively delete item */
            m->size--;
            return;
        }
    }
}
