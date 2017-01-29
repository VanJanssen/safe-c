#include "elegan-c/memory.h"

#include <stdio.h>
#include <string.h>

static void handle_zero_request(const el_handlers handlers,
                                const_cstring calling_file,
                                const int calling_line,
                                const_cstring target_function)
{
    if (handlers.error_stream)
    {
        fprintf(handlers.error_stream,
                "Error allocating memory: Function '%s' was called from file "
                "'%s' at line '%d', and zero memory was requested.\n",
                target_function, calling_file, calling_line);
    }

    if (handlers.error_function)
    {
        handlers.error_function(EXIT_FAILURE);
    }
}

static void handle_allocation_error(const el_handlers handlers,
                                    const_cstring calling_file,
                                    const int calling_line,
                                    const_cstring target_function,
                                    const size_t requested_size)
{
    if (handlers.error_stream)
    {
        fprintf(handlers.error_stream,
                "Error allocating memory: Function '%s' was called from file "
                "'%s' at line '%d' and '%zu' bytes of memory were requested, "
                "but this amount could not be allocated.\n",
                target_function, calling_file, calling_line, requested_size);
    }

    if (handlers.error_function)
    {
        handlers.error_function(EXIT_FAILURE);
    }
}

void *el_unsafe_malloc(const size_t size, const el_handlers handlers,
                       const_cstring calling_file, const int calling_line)
{
    if (size == 0)
    {
        handle_zero_request(handlers, calling_file, calling_line, __func__);
        return NULL;
    }

    void *memory = malloc(size);
    if (!memory)
    {
        handle_allocation_error(handlers, calling_file, calling_line, __func__,
                                size);
        return NULL;
    }

    return memset(memory, 0, size);
}

void el_free_address(void **pointer_address)
{
    if (pointer_address)
    {
        free(*pointer_address);
        *pointer_address = NULL;
    }
}

void *el_unsafe_calloc(const size_t number_of_elements,
                       const size_t element_size, const el_handlers handlers,
                       const_cstring calling_file, const int calling_line)
{
    if (number_of_elements == 0 || element_size == 0)
    {
        handle_zero_request(handlers, calling_file, calling_line, __func__);
        return NULL;
    }

    void *memory = calloc(number_of_elements, element_size);
    if (!memory)
    {
        handle_allocation_error(handlers, calling_file, calling_line, __func__,
                                number_of_elements * element_size);
        return NULL;
    }

    // No memset because calloc already initializes memory to all zero
    return memory;
}

void *el_unsafe_realloc(void **pointer_address, const size_t size,
                        const el_handlers handlers, const_cstring calling_file,
                        const int calling_line)
{
    if (size == 0)
    {
        handle_zero_request(handlers, calling_file, calling_line, __func__);
        el_free_address(pointer_address);
        return NULL;
    }

    if (!pointer_address || !(*pointer_address))
    {
        void *memory = el_custom_malloc(size, el_null_handlers());
        if (!memory)
        {
            handle_allocation_error(handlers, calling_file, calling_line,
                                    __func__, size);
            return NULL;
        }
        else
        {
            return memory;
        }
    }

    void *memory = realloc(*pointer_address, size);
    if (!memory)
    {
        handle_allocation_error(handlers, calling_file, calling_line, __func__,
                                size);
        return NULL;
    }

    if (memory != (*pointer_address))
    {
        (*pointer_address) = NULL;
    }

    return memory;
}
