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
                "'safe_malloc' requesting %u bytes of memory, but an error "
                "occurred allocating this amount of memory. Exiting",
                calling_function);
        exit(EXIT_FAILURE);
    }
    memset(memory, 0, size);
    return memory;
}

void safe_free_function(void** pointer)
{
    if (pointer != NULL)
    {
        free(*pointer);
        *pointer = NULL;
    }
}
