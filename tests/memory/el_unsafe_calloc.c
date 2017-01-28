#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(el_unsafe_calloc, file_null)
{
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *pointer = el_unsafe_calloc(0, 0, handlers, NULL, __LINE__);
    el_free(pointer);
}

Test(el_unsafe_calloc, zero_elements_verify_output)
{
    cr_redirect_stderr();
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *pointer = el_unsafe_calloc(0, 10, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cr_assert_stderr_eq_str(
        "Error allocating memory: Function 'el_unsafe_calloc' was called from "
        "file 'file' at line '137', and zero memory was requested.\n");
}

Test(el_unsafe_calloc, zero_size_verify_output)
{
    cr_redirect_stderr();
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *pointer = el_unsafe_calloc(10, 0, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cr_assert_stderr_eq_str(
        "Error allocating memory: Function 'el_unsafe_calloc' was called from "
        "file 'file' at line '137', and zero memory was requested.\n");
}

Test(el_unsafe_calloc, zero_both_size_verify_output)
{
    cr_redirect_stderr();
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *pointer = el_unsafe_calloc(0, 0, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cr_assert_stderr_eq_str(
        "Error allocating memory: Function 'el_unsafe_calloc' was called from "
        "file 'file' at line '137', and zero memory was requested.\n");
}

Test(el_unsafe_calloc, max_elements_verify_output)
{
    cr_redirect_stderr();
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *pointer = el_unsafe_calloc(SIZE_MAX, 1, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cstring reference_string = el_malloc(1000);
    sprintf(reference_string,
            "Error allocating memory: Function 'el_unsafe_calloc' was called "
            "from file 'file' at line '137' and '%zu' bytes of memory were "
            "requested, but this amount could not be allocated.\n",
            SIZE_MAX);
    cr_assert_stderr_eq_str(reference_string);
    el_free(reference_string);
}

Test(el_unsafe_calloc, max_size_verify_output)
{
    cr_redirect_stderr();
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    void *pointer = el_unsafe_calloc(1, SIZE_MAX, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cstring reference_string = el_malloc(1000);
    sprintf(reference_string,
            "Error allocating memory: Function 'el_unsafe_calloc' was called "
            "from file 'file' at line '137' and '%zu' bytes of memory were "
            "requested, but this amount could not be allocated.\n",
            SIZE_MAX);
    cr_assert_stderr_eq_str(reference_string);
    el_free(reference_string);
}
