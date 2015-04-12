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
    a->visited = 0;
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
    /* make sure the list is not empty */
    if (head == NULL) return 0;

    if (alias_count() == 1) {
        /* handle single element list */
        free_alias(head);
        head = NULL;
        tail = NULL;
        return 1;
    } else if (strcmp(key, head->key) == 0) {
        alias_t* a = head;
        head = a->next;
        free_alias(a);
        return 1;
    } else {
        alias_t *a = head;
        alias_t *prev = a; /* trailing ptr */
        for (; a != NULL; a = a->next)
        {
            if (strcmp(key, a->key) == 0) {
                prev->next = a->next;
                if (a == tail) tail = prev;
                free_alias(a);
                return 1;
            }
            prev = a;
        }
    }
    return 0;
}

/* frees an alias_t* object */
int
free_alias(alias_t *a)
{
    a->next = NULL;
    free(a->key);
    free(a->value);
    free(a);
    return 1;
}

void
print_aliases(void)
{
    alias_t *a = head;
    printf("ALIASES (%d):\n", alias_count());
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

void
reinit_alias_list(void)
{
    alias_t *a = head;
    for (; a != NULL; a = a->next)
        a->visited = 0;
}

char
*resolve_alias(char* key)
{
    reinit_alias_list(); 

    alias_t *a = head;
    for (; a != NULL; a = a->next)
    {
        if (strcmp(key, a->key) == 0) {
            if (a->visited == 0 && strcmp(a->key, a->value) != 0) {
                a->visited = 1;
                return resolve_alias(a->value);
            } else {
                printf("Infinite alias!\n");
                char str[] = "ERROR!";
                return str;
            }
        }
    }
    return key;   
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

int
alias_count(void)
{
    int count = 0;
    if (head == NULL) return count;

    alias_t *a = head;
    for (; a != NULL; a = a->next)
    {
        count++;
    }
    return count;
}
