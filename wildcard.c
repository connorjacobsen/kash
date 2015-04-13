#include "include/wildcard.h"

wildcard_t
*make_wildcard(char *filename)
{
  wildcard_t *wc = malloc(sizeof(wildcard_t));
  assert(wc != NULL); /* no memory if NULL */
  wc->filename = strdup(filename);
  wc->next = NULL;
  return wc;
}
 
void
wildcard_add(wildcard_t *wc)
{
  if (wchead == NULL) {
    wchead = wc;
    return;
  }
 
  wildcard_t *w = wchead;
  while (w->next != NULL)
    w = w->next;
 
  w->next = wc;
}

void
print_wildcards(void)
{
  wildcard_t *wc = wchead;
  if (wchead == NULL) return;
  while(wc != NULL) {
    printf("%s\n", wc->filename);
    if (wc->next != NULL)
      wc = wc->next;
    else
      break;
  }
}

void
clear_wildcard(void)
{
    wildcard_t *wc = wchead;
    if (wchead == NULL) return;
    while(wc != NULL) {
        wildcard_t *tmp = wc;
        if (wc->next != NULL)
            wc = wc->next;
        else
            break;
        free(tmp);
    }
    wchead = NULL;
}

int
contains_wildcard(char *str)
{
    int found = 0;
    while (*str) {
        if (*str == '*' || *str == '?') {
            found = 1;
            break;
        }
        ++str;
    }
    return found;
}
