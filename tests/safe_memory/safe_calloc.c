#include <criterion/criterion.h>

#include "safe-c/safe_memory.h"

#include <stdint.h>

Test(safe_calloc, number_of_elements_zero_expect_exit, .exit_code = 1)
{
    safe_calloc(0, 10);
}

Test(safe_calloc, element_size_zero_expect_exit, .exit_code = 1)
{
    safe_calloc(10, 0);
}

Test(safe_calloc, both_zero_expect_exit, .exit_code = 1)
{
    safe_calloc(0, 0);
}

Test(safe_calloc, number_of_elements_max_expect_exit, .exit_code = 1)
{
    safe_calloc(SIZE_MAX, 10);
}

Test(safe_calloc, element_size_max_expect_exit, .exit_code = 1)
{
    safe_calloc(10, SIZE_MAX);
}

Test(safe_calloc, both_max_expect_exit, .exit_code = 1)
{
    safe_calloc(SIZE_MAX, SIZE_MAX);
}

Test(safe_calloc, one_one_success, .exit_code = 0)
{
    void* pointer = safe_calloc(1, 1);
    safe_free(pointer);
}

Test(safe_calloc, low_values_success, .exit_code = 0)
{
    void* pointer = safe_calloc(100, 10);
    safe_free(pointer);
}

