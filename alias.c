#include "include/alias.h"

void
initialize_alias_list(void)
{
    head = NULL;
    tail = NULL;
}

/**
 * Initializes a new alias object and returns it.
 *
 * Note: This call to malloc should only allocate enough memory for
 * the three pointers that are contained within the alias_t struct.
 *
 * Additional memory will need to be initialized for the arrays of
 * characters pointed to by `key` and `value`.
 *
 * The memory for the alias_t object pointed to by `next` will be
 * initialized separately when that object is created, which must
 * be prior to setting the value of the `next` pointer.
 */
alias_t
*make_alias(void)
{
    alias_t *a = malloc(sizeof(alias_t));
    assert(a != NULL);
    a->next = NULL;
    return a;
}

/** 
 * A char is only 1 byte, so we only need to malloc strlen + 1
 * bytes of memory for a char*.
 *
 * Also need to double check that we dont allocate 2x the needed
 * memory here. So be sure to look up strcpy when reconnected to
 * the internet.
 */
int
alias(char* key, char* value)
{
    alias_t *a = make_alias();
    a->key = strdup(key);
    a->value = strdup(value);
    a->next = head; /* set next to the head of the alias_list */
    if (head == NULL)
    {
        /* list is empty */
        tail = a;
    }
    head = a;
    return 1;
}

int
unalias(char* key)
{
    alias_t *a = head;
    alias_t *prev = a; /* trailing ptr */
    for (; a != NULL; a = a->next)
    {
        if (strcmp(key, a->key) == 0)
        {
            free(a->key);
            free(a->value);
            prev->next = a->next; /* resolve gap in list */
            free(a);
            if (a == head)
            {
                head = a->next;
            }
            if (a == tail)
            {
                tail = prev;
            }
            return 1;
        }
        prev = prev->next;
    }
    return 0;
}

void
print_aliases(void)
{
    alias_t *a = head;
    printf("ALIASES:\n");
    for (; a != NULL; a = a->next)
    {
        printf("%s :: %s\n", a->key, a->value);
    }
}

/**
 * Returns the number of aliases in the alias list.
 */
unsigned int
size_of_alias_list(void)
{
    alias_t *a = head;
    unsigned int size = 0;
    while (a != tail)
    {
        ++size;
        *a = *a->next;
    }
    return size;
}

/**
 * Returns 1 (true) if the list is empty, 0 (false) if the list is not empty.
 */
int
alias_list_is_empty(void)
{
    return head == NULL;
}

int
alias_exists(char* key)
{
    alias_t *a = head;
    for (; a != NULL; a = a->next)
    {
        if (strcmp(key, a->key) == 0)
            return 1;
    }
    return 0;
}
