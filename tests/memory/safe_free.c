#include <criterion/criterion.h>

#include "elegan-c/memory.h"

Test(safe_free_function, null_succeed)
{
    safe_free_function(NULL);
}

Test(safe_free, null_succeed)
{
    void* pointer = NULL;
    safe_free_function(pointer);
}

Test(safe_free, free_malloced_succeed)
{
    void* pointer = el_malloc(50);
    safe_free(pointer);
}
