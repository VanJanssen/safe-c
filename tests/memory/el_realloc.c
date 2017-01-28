#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(el_realloc, pointer_valid_size_zero_expect_exit, .exit_code = 1)
{
    void *pointer = el_malloc(10);
    pointer = el_realloc(pointer, 0);
    el_free(pointer);
}

Test(el_realloc, pointer_valid_size_SIZE_MAX_expect_exit, .exit_code = 1)
{
    void *pointer = el_malloc(10);
    pointer = el_realloc(pointer, SIZE_MAX);
    el_free(pointer);
}

Test(el_realloc, pointer_null_size_zero_expect_exit, .exit_code = 1)
{
    void *pointer = NULL;
    pointer = el_realloc(pointer, 0);
    el_free(pointer);
}

Test(el_realloc, pointer_null_size_SIZE_MAX_expect_exit, .exit_code = 1)
{
    void *pointer = NULL;
    pointer = el_realloc(pointer, SIZE_MAX);
    el_free(pointer);
}

Test(el_realloc, pointer_null_size_valid)
{
    void *pointer = NULL;
    pointer = el_realloc(pointer, 10);
    el_free(pointer);
}

Test(el_realloc, larger_size)
{
    void *pointer = el_malloc(10);
    pointer = el_realloc(pointer, 20);
    el_free(pointer);
}

Test(el_realloc, smaller_size)
{
    void *pointer = el_malloc(20);
    pointer = el_realloc(pointer, 10);
    el_free(pointer);
}

Test(el_realloc, old_pointer_set_to_null)
{
    bool old_pointer_null = false;
    void *pointer = el_malloc(1000);
    void *initial_pointer = pointer;
    for (size_t i = 2; i < 1000; i++)
    {
        void *new_pointer = el_realloc(pointer, 1000 * i);
        if ((new_pointer != initial_pointer) && !pointer)
        {
            old_pointer_null = true;
            break;
        }
        pointer = new_pointer;
    }
    cr_assert(old_pointer_null);
}
