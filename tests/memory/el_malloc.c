#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(el_malloc, zero_expect_exit, .exit_code = 1)
{
    el_malloc(0);
}

Test(el_malloc, max_expect_exit, .exit_code = 1)
{
    void *pointer = el_malloc(SIZE_MAX);
    safe_free(pointer);
}

Test(el_malloc, one_success)
{
    void *pointer = el_malloc(1);
    safe_free(pointer);
}

Test(el_malloc, low_value_success)
{
    void *pointer = el_malloc(100);
    safe_free(pointer);
}

Test(el_malloc, multiple_low_value_success)
{
    for (size_t i = 0; i < 10; i++)
    {
        void *pointer = el_malloc(100);
        safe_free(pointer);
    }
}
