#include "safe-memory.h"

#include <stdlib.h>
#include <string.h>

void* safe_malloc_function(size_t size, const char* calling_function)
{
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
