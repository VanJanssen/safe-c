#include "safe-c/safe_memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* safe_malloc_function(size_t size, const char* calling_function)
{
    if (size == 0)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_malloc' and requested zero memory. The pointer should "
                "be explicitly set to NULL instead.\n",
                calling_function);
        exit(EXIT_FAILURE);
    }

    void* memory = malloc(size);
    if (!memory)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_malloc' requesting %zu bytes of memory, but an error "
                "occurred allocating this amount of memory. Exiting",
                calling_function, size);
        exit(EXIT_FAILURE);
    }
    memory = memset(memory, 0, size);
    return memory;
}

void safe_free_function(void** pointer_address)
{
    if (pointer_address != NULL)
    {
        free(*pointer_address);
        *pointer_address = NULL;
    }
}
