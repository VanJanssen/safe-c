#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdbool.h>
#include <stdint.h>

bool zero_elements_function_called = false;
bool zero_size_function_called = false;
bool max_elements_function_called = false;
bool max_size_function_called = false;

static void zero_elements_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        zero_elements_function_called = true;
    }
}
static void zero_size_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        zero_size_function_called = true;
    }
}

static void max_elements_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        max_elements_function_called = true;
    }
}
static void max_size_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        max_size_function_called = true;
    }
}

Test(el_custom_calloc, zero_elements_triggers_function)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = zero_elements_function;

    cr_assert_not(zero_elements_function_called);
    el_custom_calloc(0, 10, handlers);
    cr_assert(zero_elements_function_called);
}

Test(el_custom_calloc, zero_size_triggers_function)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = zero_size_function;

    cr_assert_not(zero_size_function_called);
    el_custom_calloc(10, 0, handlers);
    cr_assert(zero_size_function_called);
}

Test(el_custom_calloc, max_elements_triggers_function)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = max_elements_function;

    cr_assert_not(max_elements_function_called);
    el_custom_calloc(SIZE_MAX, 10, handlers);
    cr_assert(max_elements_function_called);
}

Test(el_custom_calloc, max_size_triggers_function)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = max_size_function;

    cr_assert_not(max_size_function_called);
    el_custom_calloc(10, SIZE_MAX, handlers);
    cr_assert(max_size_function_called);
}

Test(el_custom_calloc, handlers_out_stream_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.out_stream = NULL;

    void *pointer = el_custom_calloc(10, 10, handlers);
    el_free(pointer);
}

Test(el_custom_calloc, handlers_error_stream_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_stream = NULL;

    void *pointer = el_custom_calloc(10, 10, handlers);
    el_free(pointer);
}

Test(el_custom_calloc, handlers_error_function_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;

    void *pointer = el_custom_calloc(10, 10, handlers);
    el_free(pointer);
}

Test(el_custom_calloc, handlers_all_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.out_stream = NULL;
    handlers.error_stream = NULL;
    handlers.error_function = NULL;

    void *pointer = el_custom_calloc(10, 10, handlers);
    el_free(pointer);
}
