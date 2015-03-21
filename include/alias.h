#ifndef ALIAS_H_
#define ALIAS_H_
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

typedef struct alias_t {
    char *key;              /* the name used to identify the alias. */
    char *value;            /* the word for which the name stands in. */
    struct alias_t *next;   /* the next alias in the list. */
} alias_t;

/* The start of the alias list. */
struct alias_t *head;

/* The tail of the alias list. */
struct alias_t *tail;

/* Initializes the alias list, should run on startup. */
void initialize_alias_list(void);

/**
 * Creates an alias between a name and a word.
 *
 * Places the alias at the head of the alias list.
 * This causes newer aliases to "overwrite" older ones.
 */
int alias(char *key, char *value);

/* Removes an alias between a name and a word. */
int unalias(char *key);

/* Prints out all exists aliases. */
void print_aliases(void);

/* Substitutes the word for the alias name. */
char *resolvealias(char *key);

/* Returns true if an alias exists for the given name. */
int alias_exists(char* key);


#endif /* ALIAS_H_ */