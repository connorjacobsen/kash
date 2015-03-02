#include <stdio.h>
#include "include/minunit.h"
#include "include/element.h"
#include "include/map.h"

int tests_run = 0;

static char *test_map()
{
    map_t* m = make_map();
    mu_assert("Map initialized incorrectly", map_size(m) == 0);
    map_put(m, "hello", "world");
    mu_assert("Map put failed", map_size(m) == 1);

    /* check contents of map */
    mu_assert("Map contains failed", map_contains(m, "hello") == 1);
    mu_assert("Map contains failed", map_contains(m, "foo") == 0);

    mu_assert("Map get failed", map_get(m, "hello") == "world");

    map_del(m, "hello");
    mu_assert("Map contains failed -- post del", map_contains(m, "hello") == 0);
    mu_assert("Map del incorrectly", map_size(m) == 0);
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