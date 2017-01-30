#include <criterion/criterion.h>

#include "elegan-c/memory.h"

#include <stdbool.h>
#include <stdint.h>

bool pointer_null_size_zero_function_called = false;
bool pointer_null_size_max_function_called = false;
bool pointer_null_size_valid_function_called = false;
bool pointer_valid_size_zero_function_called = false;
bool pointer_valid_size_max_function_called = false;
bool pointer_valid_size_valid_function_called = false;

static void pointer_null_size_zero_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        pointer_null_size_zero_function_called = true;
    }
}

static void pointer_null_size_max_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        pointer_null_size_max_function_called = true;
    }
}

static void pointer_null_size_valid_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        pointer_null_size_valid_function_called = true;
    }
}

static void pointer_valid_size_zero_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        pointer_valid_size_zero_function_called = true;
    }
}

static void pointer_valid_size_max_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        pointer_valid_size_max_function_called = true;
    }
}

static void pointer_valid_size_valid_function(int value)
{
    if (value == EXIT_FAILURE)
    {
        pointer_valid_size_valid_function_called = true;
    }
}

Test(el_custom_realloc, pointer_null_size_zero_triggers_function)
{
    void *pointer = NULL;
    el_handlers handlers = el_default_handlers();
    handlers.error_function = pointer_null_size_zero_function;

    cr_assert_not(pointer_null_size_zero_function_called);
    pointer = el_custom_realloc(pointer, 0, handlers);
    cr_assert(pointer_null_size_zero_function_called);

    el_free(pointer);
}

Test(el_custom_realloc, pointer_null_size_max_triggers_function)
{
    void *pointer = NULL;
    el_handlers handlers = el_default_handlers();
    handlers.error_function = pointer_null_size_max_function;

    cr_assert_not(pointer_null_size_max_function_called);
    pointer = el_custom_realloc(pointer, SIZE_MAX, handlers);
    cr_assert(pointer_null_size_max_function_called);

    el_free(pointer);
}

Test(el_custom_realloc, pointer_null_size_valid_not_triggers_function)
{
    void *pointer = NULL;
    el_handlers handlers = el_default_handlers();
    handlers.error_function = pointer_null_size_valid_function;

    cr_assert_not(pointer_null_size_valid_function_called);
    pointer = el_custom_realloc(pointer, 100, handlers);
    cr_assert_not(pointer_null_size_valid_function_called);

    el_free(pointer);
}

Test(el_custom_realloc, pointer_valid_size_zero_triggers_function)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = pointer_valid_size_zero_function;

    cr_assert_not(pointer_valid_size_zero_function_called);
    pointer = el_custom_realloc(pointer, 0, handlers);
    cr_assert(pointer_valid_size_zero_function_called);

    el_free(pointer);
}

Test(el_custom_realloc, pointer_valid_size_max_triggers_function)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = pointer_valid_size_max_function;

    cr_assert_not(pointer_valid_size_max_function_called);
    pointer = el_custom_realloc(pointer, SIZE_MAX, handlers);
    cr_assert(pointer_valid_size_max_function_called);

    el_free(pointer);
}

Test(el_custom_realloc, pointer_valid_size_valid_not_triggers_function)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = pointer_valid_size_valid_function;

    cr_assert_not(pointer_valid_size_valid_function_called);
    pointer = el_custom_realloc(pointer, 100, handlers);
    cr_assert_not(pointer_valid_size_valid_function_called);

    el_free(pointer);
}

Test(el_custom_realloc, handlers_out_stream_null)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.out_stream = NULL;

    pointer = el_custom_realloc(pointer, 100, handlers);
    el_free(pointer);
}

Test(el_custom_realloc, handlers_error_stream_null)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_stream = NULL;

    pointer = el_custom_realloc(pointer, 100, handlers);
    el_free(pointer);
}

Test(el_custom_realloc, handlers_error_function_null)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;

    pointer = el_custom_realloc(pointer, 100, handlers);
    el_free(pointer);
}

Test(el_custom_realloc, handlers_all_null)
{
    void *pointer = el_malloc(10);
    pointer = el_custom_realloc(pointer, 100, el_null_handlers());
    el_free(pointer);
}
