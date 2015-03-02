#include <stdio.h>
#include "include/minunit.h"
#include "include/element.h"
#include "include/map.h"

int tests_run = 0;

static char *test_map()
{
    map_t* m = make_map();
    mu_assert("Map initialized incorrectly", map_size(m) == 0);
    return 0;
}

static char *all_tests()
{
    mu_run_test(test_map);
    return 0;
}

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