#include <criterion/criterion.h>

#include "elegan-c/common.h"

Test(el_default_handlers, verify_default_values)
{
    el_handlers handlers = el_default_handlers();
    cr_assert_eq(handlers.out_stream, stdout);
    cr_assert_eq(handlers.error_stream, stderr);
    cr_assert_eq(handlers.error_function, exit);
}