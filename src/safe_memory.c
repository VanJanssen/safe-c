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

void* safe_calloc_function(const size_t number_of_elements,
        const size_t element_size, const char* calling_function)
{
    if (number_of_elements == 0)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_calloc' and requested zero memory (number of elements "
                "== 0). The pointer should be explicitly set to NULL instead.\n",
                calling_function);
        exit(EXIT_FAILURE);
    }

    if (element_size == 0)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_calloc' and requested zero memory (element size == 0). "
                "The pointer should be explicitly set to NULL instead.\n",
                calling_function);
        exit(EXIT_FAILURE);
    }

    void* memory = calloc(number_of_elements, element_size);
    if (!memory)
    {
        fprintf(stderr, "Error allocating memory: The function %s called "
                "'safe_calloc' requesting %zu elements with size %zu each, but "
                "an error occurred allocating this amount of memory.\n",
                calling_function, number_of_elements, element_size);
        exit(EXIT_FAILURE);
    }
    // No memset because calloc already initializes memory to all zero.

    return memory;
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
