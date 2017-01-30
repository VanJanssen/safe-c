#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(el_unsafe_realloc, file_null)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    pointer = el_unsafe_realloc(&pointer, 0, handlers, NULL, __LINE__);
    el_free(pointer);
}

Test(el_unsafe_calloc, line_negative)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    pointer = el_unsafe_realloc(&pointer, 0, handlers, __FILE__, -50);
    el_free(pointer);
}

Test(el_unsafe_realloc, pointer_address_null_size_zero_verify_output)
{
    cr_redirect_stderr();
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *pointer = el_unsafe_realloc(NULL, 0, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cr_assert_stderr_eq_str(
        "Error allocating memory: Function 'el_unsafe_realloc' was called from "
        "file 'file' at line '137', and zero memory was requested.\n");
}

Test(el_unsafe_realloc, pointer_null_size_zero_verify_output)
{
    cr_redirect_stderr();
    void *pointer = NULL;
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    pointer = el_unsafe_realloc(&pointer, 0, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cr_assert_stderr_eq_str(
        "Error allocating memory: Function 'el_unsafe_realloc' was called from "
        "file 'file' at line '137', and zero memory was requested.\n");
}

Test(el_unsafe_realloc, pointer_valid_size_zero_verify_output)
{
    cr_redirect_stderr();
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    pointer = el_unsafe_realloc(&pointer, 0, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cr_assert_stderr_eq_str(
        "Error allocating memory: Function 'el_unsafe_realloc' was called from "
        "file 'file' at line '137', and zero memory was requested.\n");
}

Test(el_unsafe_realloc, pointer_null_size_max_verify_output)
{
    cr_redirect_stderr();
    void *pointer = NULL;
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *new_pointer =
        el_unsafe_realloc(&pointer, SIZE_MAX, handlers, "file", 137);
    el_free(pointer);
    el_free(new_pointer);

    fflush(stderr);
    cstring reference_string = el_malloc(1000);
    sprintf(reference_string,
            "Error allocating memory: Function 'el_unsafe_realloc' was called "
            "from file 'file' at line '137' and '%zu' bytes of memory were "
            "requested, but this amount could not be allocated.\n",
            SIZE_MAX);
    cr_assert_stderr_eq_str(reference_string);
    el_free(reference_string);
}

Test(el_unsafe_realloc, pointer_valid_size_max_verify_output)
{
    cr_redirect_stderr();
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *new_pointer =
        el_unsafe_realloc(&pointer, SIZE_MAX, handlers, "file", 137);
    el_free(pointer);
    el_free(new_pointer);

    fflush(stderr);
    cstring reference_string = el_malloc(1000);
    sprintf(reference_string,
            "Error allocating memory: Function 'el_unsafe_realloc' was called "
            "from file 'file' at line '137' and '%zu' bytes of memory were "
            "requested, but this amount could not be allocated.\n",
            SIZE_MAX);
    cr_assert_stderr_eq_str(reference_string);
    el_free(reference_string);
}
