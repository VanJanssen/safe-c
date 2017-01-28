#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(el_calloc, number_of_elements_zero_expect_exit, .exit_code = 1)
{
    el_calloc(0, 10);
}

Test(el_calloc, element_size_zero_expect_exit, .exit_code = 1)
{
    el_calloc(10, 0);
}

Test(el_calloc, both_zero_expect_exit, .exit_code = 1) { el_calloc(0, 0); }

Test(el_calloc, number_of_elements_max_expect_exit, .exit_code = 1)
{
    void *pointer = el_calloc(SIZE_MAX, 10);
    el_free(pointer);
}

Test(el_calloc, element_size_max_expect_exit, .exit_code = 1)
{
    void *pointer = el_calloc(10, SIZE_MAX);
    el_free(pointer);
}

Test(el_calloc, both_max_expect_exit, .exit_code = 1)
{
    void *pointer = el_calloc(SIZE_MAX, SIZE_MAX);
    el_free(pointer);
}

Test(el_calloc, one_one_success, .exit_code = 0)
{
    void *pointer = el_calloc(1, 1);
    el_free(pointer);
}

Test(el_calloc, low_values_success, .exit_code = 0)
{
    void *pointer = el_calloc(100, 10);
    el_free(pointer);
}

Test(el_calloc, multiple_low_value_success)
{
    for (size_t i = 0; i < 10; i++)
    {
        void *pointer = el_calloc(100, 10);
        el_free(pointer);
    }
}
