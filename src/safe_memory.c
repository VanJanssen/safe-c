#include "safe-c/safe_memory.h"

#include <stdio.h>
#include <string.h>

void* safe_malloc_function(const size_t size, const char* calling_function)
{
    if (size == 0)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_malloc' and requested zero memory. The pointer should "
                "be explicitly set to NULL instead.\n", calling_function);
        exit(EXIT_FAILURE);
    }

    void* memory = malloc(size);
    if (!memory)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_malloc' requesting %zu bytes of memory, but an error "
                "occurred allocating this amount of memory.\n",
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

void* safe_realloc_function(void** pointer_address, const size_t size,
        const char* calling_function)
{
    if (!pointer_address)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_realloc', but the address to the pointer to be "
                "reallocated is NULL.\n", calling_function);
        exit(EXIT_FAILURE);
    }

    if (size == 0)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_realloc' and requested zero memory. The pointer should "
                "be explicitly set to NULL instead.\n", calling_function);
        exit(EXIT_FAILURE);
    }

    void* memory = realloc(*pointer_address, size);
    if (!memory)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_realloc' requesting %zu bytes of memory, but an error "
                "occurred allocating this amount of memory.\n",
                calling_function, size);
        exit(EXIT_FAILURE);
    }

    if (memory != *pointer_address)
    {
        // If the memory block is moved, relloc frees the pointer. To ensure
        // the same behaviour as `safe_free`, we set the pointer to NULL.
        *pointer_address = NULL;
    }

    return memory;
}
