#include <criterion/criterion.h>

#include "elegan-c/memory.h"

Test(el_free_address, address_null) { el_free_address(NULL); }

Test(el_free_address, address_valid_pointer_null)
{
    void *pointer = NULL;
    el_free_address(&pointer);

    cr_assert_null(pointer);
}

Test(el_free_address, address_valid_pointer_valid)
{
    void *pointer = el_malloc(10);
    el_free_address(&pointer);

    cr_assert_null(pointer);
}

Test(el_free, pointer_null)
{
    void *pointer = NULL;
    el_free(pointer);
    cr_assert_null(pointer);
}

Test(el_free, pointer_valid)
{
    void *pointer = el_malloc(50);
    el_free(pointer);
    cr_assert_null(pointer);
}
