#include <criterion/criterion.h>

#include "safe-c/safe_memory.h"

#include <stdint.h>

Test(safe_realloc, address_null_size_valid_expect_exit, .exit_code = 1)
{
    safe_realloc_function(NULL, 10, __FUNCTION__);
}

Test(safe_realloc, pointer_valid_size_zero_expect_exit, .exit_code = 1)
{
    void* pointer = safe_malloc(10);
    safe_realloc(pointer, 0);
}

Test(safe_realloc, pointer_valid_size_SIZE_MAX_expect_exit, .exit_code = 1)
{
    void* pointer = safe_malloc(10);
    safe_realloc(pointer, SIZE_MAX);
}

Test(safe_realloc, pointer_NULL_size_valid)
{
    void* pointer = NULL;
    pointer = safe_realloc(pointer, 10);
    safe_free(pointer);
}

Test(safe_realloc, larger_size)
{
    void* pointer = safe_malloc(10);
    pointer = safe_realloc(pointer, 20);
    safe_free(pointer);
}

Test(safe_realloc, smaller_size)
{
    void* pointer = safe_malloc(20);
    pointer = safe_realloc(pointer, 10);
    safe_free(pointer);
}