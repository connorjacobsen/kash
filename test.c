#include <stdio.h>
#include "include/minunit.h"
#include "include/element.h"
#include "include/map.h"

int tests_run = 0;

int main(int argc, char** argv)
{
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}