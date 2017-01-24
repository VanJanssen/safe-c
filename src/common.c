#include "elegan-c/common.h"

#include <stdlib.h>

el_handlers el_default_handlers(void)
{
    el_handlers handlers;
    handlers.out_stream = stdout;
    handlers.error_stream = stderr;
    handlers.error_function = exit;
    return handlers;
}
