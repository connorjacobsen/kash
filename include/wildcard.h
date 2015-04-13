#ifndef WILDCARD_H_
#define WILDCARD_H_

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <fnmatch.h>
#include <assert.h>
#include <string.h>

typedef struct wildcard_t {
  char *filename;
  struct wildcard_t *next;
} wildcard_t;

/* list initially empty */
struct wildcard_t *wchead;
 
wildcard_t
*make_wildcard(char *filename);
 
void
wildcard_add(wildcard_t *wc);

void
clear_wildcard(void);

void
print_wildcards(void);

int
contains_wildcard(char *str);

#endif /* WILDCARD_H_ */