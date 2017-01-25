#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(safe_realloc, address_null_size_valid_expect_exit, .exit_code = 1)
{
    void *shouldnt_allocate = safe_realloc_function(NULL, 10, __FUNCTION__);
    el_free(shouldnt_allocate);
}

Test(safe_realloc, pointer_valid_size_zero_expect_exit, .exit_code = 1)
{
    void *pointer = el_malloc(10);
    pointer = safe_realloc(pointer, 0);
    el_free(pointer);
}

Test(safe_realloc, pointer_valid_size_SIZE_MAX_expect_exit, .exit_code = 1)
{
    void *pointer = el_malloc(10);
    pointer = safe_realloc(pointer, SIZE_MAX);
    el_free(pointer);
}

Test(safe_realloc, pointer_NULL_size_valid)
{
    void *pointer = NULL;
    pointer = safe_realloc(pointer, 10);
    el_free(pointer);
}

Test(safe_realloc, larger_size)
{
    void *pointer = el_malloc(10);
    pointer = safe_realloc(pointer, 20);
    el_free(pointer);
}

Test(safe_realloc, smaller_size)
{
    void *pointer = el_malloc(20);
    pointer = safe_realloc(pointer, 10);
    el_free(pointer);
}
