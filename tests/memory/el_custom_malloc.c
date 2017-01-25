#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdbool.h>
#include <stdint.h>

bool zero_function_called = false;
bool max_function_called = false;

static void zero_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        zero_function_called = true;
    }
}

static void max_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        max_function_called = true;
    }
}

Test(el_custom_malloc, zero_triggers_function)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = zero_function;

    cr_assert_not(zero_function_called);
    el_custom_malloc(0, handlers);
    cr_assert(zero_function_called);
}

Test(el_custom_malloc, max_triggers_function)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = max_function;

    cr_assert_not(max_function_called);
    void *pointer = el_custom_malloc(SIZE_MAX, handlers);
    cr_assert(max_function_called);

    el_free(pointer);
}

Test(el_custom_malloc, handlers_out_stream_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.out_stream = NULL;

    void *pointer = el_custom_malloc(10, handlers);
    el_free(pointer);
}

Test(el_custom_malloc, handlers_error_stream_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_stream = NULL;

    void *pointer = el_custom_malloc(10, handlers);
    el_free(pointer);
}

Test(el_custom_malloc, handlers_error_function_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;

    void *pointer = el_custom_malloc(10, handlers);
    el_free(pointer);
}

Test(el_custom_malloc, handlers_all_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.out_stream = NULL;
    handlers.error_stream = NULL;
    handlers.error_function = NULL;

    void *pointer = el_custom_malloc(10, handlers);
    el_free(pointer);
}
