#include "safe-memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* safe_malloc_function(size_t size, const char* calling_function)
{
    if (size == 0)
    {
        return NULL;
    }

    void* memory = malloc(size);
    if (!memory)
    {
        fprintf(stderr, "Error: not enough memory for malloc in function: %s",
                calling_function);
        exit(EXIT_FAILURE);
    }
    memset(memory, 0, size);
    return memory;
}
