#include <criterion/criterion.h>

#include "elegan-c/common.h"

Test(el_null_handlers, verify_values)
{
    el_handlers handlers = el_null_handlers();
    cr_assert_null(handlers.out_stream);
    cr_assert_null(handlers.error_stream);
    cr_assert_null(handlers.error_function);
}
