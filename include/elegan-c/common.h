#ifndef ELEGAN_C_COMMON_H_
#define ELEGAN_C_COMMON_H_

#include <stdio.h>

/**
 * el_handlers
 *
 * This struct can be passed to various function to indicate which streams the
 * function should use and what function to call when an error occurs.
 */
typedef struct
{
    FILE *out_stream;
    FILE *error_stream;
    void (*error_function)(int exit_code);
} el_handlers;

/**
 * Returns an `el_handlers` struct initialzed with the default values:
 *      - out_stream = stdout
 *      - error_stream = stderr
 *      - error_function = exit
 */
el_handlers el_default_handlers(void);

#endif /* ELEGAN_C_COMMON_H_ */