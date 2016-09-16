#include <criterion/criterion.h>

#include "safe-c/safe_memory.h"

#include <stdint.h>

Test(safe_malloc, zero_expect_exit, .exit_code = 1)
{
    safe_malloc(0);
}

Test(safe_malloc, max_expect_exit, .exit_code = 1)
{
    safe_malloc(SIZE_MAX);
}

