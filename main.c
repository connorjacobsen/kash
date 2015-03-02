#include "include/element.h"

int main(int argc, char* argv[])
{
    element_t* el = element_new_element("hello", "world");
    printf("KEY: %s\n", el->key);
    printf("VALUE: %s\n", el->value);

    return 0;
}
