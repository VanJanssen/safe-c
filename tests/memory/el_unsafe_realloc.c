#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "elegan-c/memory.h"

#include <stdint.h>

Test(el_unsafe_realloc, file_null)
{
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    pointer = el_unsafe_realloc(pointer, 0, handlers, NULL, __LINE__);
    el_free(pointer);
}

Test(el_unsafe_realloc, zero_verify_output)
{
    cr_redirect_stderr();
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    pointer = el_unsafe_realloc(pointer, 0, handlers, "file", 137);
    el_free(pointer);

    fflush(stderr);
    cr_assert_stderr_eq_str(
        "Error allocating memory: Function 'el_unsafe_realloc' was called from "
        "file 'file' at line '137', and zero memory was requested.\n");
}

Test(el_unsafe_realloc, max_verify_output)
{
    cr_redirect_stderr();
    void *pointer = el_malloc(10);
    el_handlers handlers = el_default_handlers();
    handlers.error_function = NULL;
    pointer = el_unsafe_realloc(pointer, SIZE_MAX, handlers, "file", 137);
    el_free(pointer);

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
