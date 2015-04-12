#include <stdio.h>
#include <assert.h>
#include "include/minunit.h"

#include "include/util.h"

int tests_run = 0;

static char
*test_split_string_1()
{
    char *my_str = "foo bar baz";
    char **str_arr = split_string(my_str);
    unsigned int size = str_array_size(str_arr);
    mu_assert("error!", size == 3);

    char *str2 = "foo";
    //char **str_arr2 = split_string(str2);
    //size = str_array_size(str_arr);
    //mu_assert("error!", size == 1);
    return 0;
}

static char
*all_tests()
{
    mu_run_test(test_split_string_1);
    return 0;
}

int
main(int argc, char** argv)
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