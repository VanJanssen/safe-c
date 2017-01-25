#include <criterion/criterion.h>

#include "elegan-c/memory.h"

Test(el_free_address, null_succeed) { el_free_address(NULL); }

Test(el_free, null_succeed)
{
    void *pointer = NULL;
    el_free_address(pointer);
}

Test(el_free, free_malloced_succeed)
{
    void *pointer = el_malloc(50);
    el_free(pointer);
}
