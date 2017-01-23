#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(safe_malloc, zero_expect_exit, .exit_code = 1)
{
    safe_malloc(0);
}

Test(safe_malloc, max_expect_exit, .exit_code = 1)
{
    void* pointer = safe_malloc(SIZE_MAX);
    safe_free(pointer);
}

Test(safe_malloc, one_success, .exit_code = 0)
{
    void* pointer = safe_malloc(1);
    safe_free(pointer);
}

Test(safe_malloc, low_value_success, .exit_code = 0)
{
    void* pointer = safe_malloc(100);
    safe_free(pointer);
}

