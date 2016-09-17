#include <criterion/criterion.h>

#include "safe-c/safe_memory.h"

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
    void* pointer = safe_malloc(50);
    safe_free_function(pointer);
}
