#ifndef SAFE_MEMORY_H_
#define SAFE_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "elegan-c/common.h"
#include "elegan-c/string.h"

/**
 * Predictiable memory allocation with customizable boundary and error checking
 * and logging for efficient debugging. It is not recommended to use this
 * function directly, use these wrapper macros instead:
 *      - el_malloc for most purposes
 *      - el_custom_malloc if you want to specify the handlers yourself.
 *
 * @param size
 *      The size in bytes to be allocated. Be aware that size is an unsigned
 *      type, passing signed values can lead to conversion errors.
 *      If `size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `handlers.error_stream`, call
 *      `handlers.error_function` and return NULL.
 *
 * @param handlers
 *      Use this parameter to specify the behaviour of this function on errors.
 *      The error message will be written to the `handlers.error_function` file
 *      descriptor, set this to NULL to supress the message.
 *      The function `handlers.error_function` will be called on an error,
 *      unless it is set to NULL.
 *
 * @param calling_file
 *      The file from which this function was called, this will be mentioned
 *      in the error message to aid debugging. Set this to `__FILE__`.
 *
 * @param calling_line
 *      The line from which this function was called, this will be mentioned
 *      in the error message to aid debugging. Set this to `__LINE__`.
 *
 * @return
 *      The return value will be a pointer to the allocated memory, the memory
 *      will be initialized to all zero.
 *      If an error occurs, this function will return NULL.
 */
void *el_unsafe_malloc(const size_t size, const el_handlers handlers,
                       const_cstring calling_file, const int calling_line);

/**
 * Predictiable memory allocation with customizable boundary and error checking
 * and logging for efficient debugging.
 *
 * @param size
 *      The size in bytes to be allocated. Be aware that size is an unsigned
 *      type, passing signed values can lead to conversion errors.
 *      If `size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `handlers.error_stream`, call
 *      `handlers.error_function` and return NULL.
 *
 * @param handlers
 *      Use this parameter to specify the behaviour of this function on errors.
 *      The error message will be written to the `handlers.error_function` file
 *      descriptor, set this to NULL to supress the message.
 *      The function `handlers.error_function` will be called on an error,
 *      unless it is set to NULL.
 *
 * @return
 *      The return value will be a pointer to the allocated memory, the memory
 *      will be initialized to all zero.
 *      If an error occurs, this function will return NULL.
 */
#define el_custom_malloc(size, handlers)                                       \
    el_unsafe_malloc((size), (handlers), __FILE__, __LINE__)

/**
 * Predictiable memory allocation with strict boundary and error checking and
 * and logging for efficient debugging.
 *
 * @param size
 *      The size in bytes to be allocated. Be aware that size is an unsigned
 *      type, passing signed values can lead to conversion errors.
 *      If `size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `stderr` and call `exit()`.
 *
 * @return
 *      The return value will be a pointer to the allocated memory, the memory
 *      will be initialized to all zero.
 *      If for some reason the memory couldn't be allocated, this function will
 *      call `exit()` and print an error message indicating the call location
 *      and the amount of memory requested.
 */
#define el_malloc(size) el_custom_malloc((size), el_default_handlers())

/**
 * Frees previously allocated memory and sets the passed pointer to NULL.
 *
 * This function requires an address to a pointer, the macro function
 * `el_free` can be used to call this function with the pointer itself, so
 * usage is the same as that of `free()`. The macro calls this function with
 * the address of the passed pointer and the proper cast.
 *
 * @param pointer_address
 *      The address of the pointer variable that shall be freed and set to
 *      NULL. If `pointer_address` is NULL, nothing happens.
 */
void el_free_address(void **pointer_address);

/**
 * Frees previously allocated memory and sets the passed pointer to NULL.
 *
 * @param pointer
 *      The pointer variable that shall be freed and set to NULL.
 */
#define el_free(pointer) el_free_address((void **)&(pointer))

/**
 * Predictiable memory allocation with customizable boundary and error checking
 * and logging for efficient debugging. It is not recommended to use this
 * function directly, use these wrapper macros instead:
 *      - el_calloc for most purposes
 *      - el_custom_calloc if you want to specify the handlers yourself.
 *
 * @param number_of_elements
 *      The number of elements (each with size `element_size`) to be allocated.
 *      Be aware that the number of elements is an unsigned type, passing signed
 *      values can lead to conversion errors.
 *      If `number_of_elements == 0`, or the requested number can not be
 *      allocated, this function will write an error message to
 *      `handlers.error_stream`, call `handlers.error_function` and return NULL.
 *
 * @param element_size
 *      The size in bytes of each element to be allocated. Be aware that
 *      element_size is an unsigned type, passing signed values can lead to
 *      conversion errors.
 *      If `element_size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `handlers.error_stream`, call
 *      `handlers.error_function` and return NULL.
 *
 * @param handlers
 *      Use this parameter to specify the behaviour of this function on errors.
 *      The error message will be written to the `handlers.error_function` file
 *      descriptor, set this to NULL to supress the message.
 *      The function `handlers.error_function` will be called on an error,
 *      unless it is set to NULL.
 *
 * @param calling_file
 *      The file from which this function was called, this will be mentioned
 *      in the error message to aid debugging. Set this to `__FILE__`.
 *
 * @param calling_line
 *      The line from which this function was called, this will be mentioned
 *      in the error message to aid debugging. Set this to `__LINE__`.
 *
 * @return
 *      The return value will be a pointer to the allocated memory, the memory
 *      will be initialized to all zero.
 *      If an error occurs, this function will return NULL.
 */
void *el_unsafe_calloc(const size_t number_of_elements,
                       const size_t element_size, const el_handlers handlers,
                       const_cstring calling_file, const int calling_line);

/**
 * Predictiable memory allocation with customizable boundary and error checking
 * and logging for efficient debugging.
 *
 * @param number_of_elements
 *      The number of elements (each with size `element_size`) to be allocated.
 *      Be aware that the number of elements is an unsigned type, passing signed
 *      values can lead to conversion errors.
 *      If `number_of_elements == 0`, or the requested number can not be
 *      allocated, this function will write an error message to
 *      `handlers.error_stream`, call `handlers.error_function` and return NULL.
 *
 * @param element_size
 *      The size in bytes of each element to be allocated. Be aware that
 *      element_size is an unsigned type, passing signed values can lead to
 *      conversion errors.
 *      If `element_size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `handlers.error_stream`, call
 *      `handlers.error_function` and return NULL.
 *
 * @param handlers
 *      Use this parameter to specify the behaviour of this function on errors.
 *      The error message will be written to the `handlers.error_function` file
 *      descriptor, set this to NULL to supress the message.
 *      The function `handlers.error_function` will be called on an error,
 *      unless it is set to NULL.
 *
 * @return
 *      The return value will be a pointer to the allocated memory, the memory
 *      will be initialized to all zero.
 *      If an error occurs, this function will return NULL.
 */
#define el_custom_calloc(number_of_elements, element_size, handlers)           \
    el_unsafe_calloc((number_of_elements), (element_size), (handlers),         \
                     __FILE__, __LINE__)

/**
 * Predictiable memory allocation with strict boundary and error checking and
 * and logging for efficient debugging.
 *
 * @param number_of_elements
 *      The number of elements (each with size `element_size`) to be allocated.
 *      Be aware that the number of elements is an unsigned type, passing signed
 *      values can lead to conversion errors.
 *      If `number_of_elements == 0`, or the requested number can not be
 *      allocated, , this function will write an error message to `stderr` and
 *      call `exit()`
 *
 * @param element_size
 *      The size in bytes of each element to be allocated. Be aware that
 *      element_size is an unsigned type, passing signed values can lead to
 *      conversion errors.
 *      If `element_size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `stderr` and call `exit()`
 *
 * @return
 *      If for some reason the memory couldn't be allocated, this function will
 *      call `exit()` and print an error message indicating the call location
 *      and the amount of memory requested.
 */
#define el_calloc(number_of_elements, element_size)                            \
    el_custom_calloc((number_of_elements), (element_size),                     \
                     el_default_handlers())

/**
 * Predictiable memory reallocation with customizable boundary and error
 * checking and logging for efficient debugging. It is not recommended to use
 * this function directly, use these wrapper macros instead:
 *      - el_realloc for most purposes
 *      - el_custom_realloc if you want to specify the handlers yourself.
 *
 * @param pointer_address
 *      The address of the pointer pointing to the memory block to be
 *      reallocated.
 *      This function changes the size of this memory block to `size` bytes. The
 *      contents will be unchanged in the range from the start of the region up
 *      to the minimum of the old and the new size.
 *      If `pointer_address == NULL` or `(*pointer_address) == NULL`, the
 *      behavior of this function will be the same as the `el_malloc` functions.
 *      If `pointer_address != NULL` and `(*pointer_address) != NULL`, the
 *      pointer must be valid (returned by a earlier call to a memory allocation
 *      function).
 *
 * @param size
 *      The new size in bytes for the memory block. Be aware that size is an
 *      unsigned type, passing signed values can lead to conversion errors.
 *      If `size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `handlers.error_stream`, call
 *      `handlers.error_function` and return NULL.
 *      If `size == 0`, it will be equivalent to calling `el_free`, if the
 *      requested size can not be allocated, this function will return NULL.
 *      If the new size is larger than the old size, the added memory will
 *      _not_ be initialized.
 *
 * @param handlers
 *      Use this parameter to specify the behaviour of this function on errors.
 *      The error message will be written to the `handlers.error_function` file
 *      descriptor, set this to NULL to supress the message.
 *      The function `handlers.error_function` will be called on an error,
 *      unless it is set to NULL.
 *
 * @param calling_file
 *      The file from which this function was called, this will be mentioned
 *      in the error message to aid debugging. Set this to `__FILE__`.
 *
 * @param calling_line
 *      The line from which this function was called, this will be mentioned
 *      in the error message to aid debugging. Set this to `__LINE__`.
 *
 * @return
 *      The return value will be a pointer to the reallocated memory.
 *      If the new size is larger than the old size, the added memory will _not_
 *      be initialized.
 *      If the memory block was moved, the returned pointer will point to this
 *      new location, the passed pointer will be set to NULL.
 *      If this function fails, the original block is left untouched (it is not
 *      freed or moved) and it will return NULL.
 */
void *el_unsafe_realloc(void **pointer_address, const size_t size,
                        const el_handlers handlers, const_cstring calling_file,
                        const int calling_line);

/**
 * Predictiable memory reallocation with customizable boundary and error
 * checking and logging for efficient debugging.
 *
 * @param pointer
 *      The pointer pointing to the memory block to be reallocated.
 *      This function changes the size of this memory block to `size` bytes. The
 *      contents will be unchanged in the range from the start of the region up
 *      to the minimum of the old and the new size.
 *      If `address == NULL`, the behavior of this function will be the same as
 *      the `el_malloc` functions.
 *      If `pointer != NULL` the pointer must be valid (returned by a earlier
 *      call to a memory allocation function).
 *
 * @param size
 *      The new size in bytes for the memory block. Be aware that size is an
 *      unsigned type, passing signed values can lead to conversion errors.
 *      If `size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `handlers.error_stream`, call
 *      `handlers.error_function` and return NULL.
 *      If `size == 0`, it will be equivalent to calling `el_free`, if the
 *      requested size can not be allocated, this function will return NULL.
 *      If the new size is larger than the old size, the added memory will
 *      _not_ be initialized.
 *
 * @param handlers
 *      Use this parameter to specify the behaviour of this function on errors.
 *      The error message will be written to the `handlers.error_function` file
 *      descriptor, set this to NULL to supress the message.
 *      The function `handlers.error_function` will be called on an error,
 *      unless it is set to NULL.
 *
 * @return
 *      The return value will be a pointer to the reallocated memory.
 *      If the new size is larger than the old size, the added memory will _not_
 *      be initialized.
 *      If the memory block was moved, the returned pointer will point to this
 *      new location, the passed pointer will be set to NULL.
 *      If this function fails, the original block is left untouched (it is not
 *      freed or moved) and it will return NULL.
 */
#define el_custom_realloc(pointer, size, handlers)                             \
    el_unsafe_realloc((void **)&(pointer), (size), (handlers), __FILE__,       \
                      __LINE__)

/**
 * Predictiable memory allocation with strict boundary and error checking and
 * and logging for efficient debugging.
 *
 * @param pointer
 *      The pointer pointing to the memory block to be reallocated.
 *      This function changes the size of this memory block to `size` bytes. The
 *      contents will be unchanged in the range from the start of the region up
 *      to the minimum of the old and the new size.
 *      If `address == NULL`, the behavior of this function will be the same as
 *      the `el_malloc` functions.
 *      If `pointer != NULL` the pointer must be valid (returned by a earlier
 *      call to a memory allocation function).
 *
 * @param size
 *      The new size in bytes for the memory block. Be aware that size is an
 *      unsigned type, passing signed values can lead to conversion errors.
 *      If `size == 0`, or the requested size can not be allocated, this
 *      function will write an error message to `stderr` and call `exit()`.
 *      If the new size is larger than the old size, the added memory will
 *      _not_ be initialized.
 *
 * @return
 *      The return value will be a pointer to the reallocated memory.
 *      If the new size is larger than the old size, the added memory will _not_
 *      be initialized.
 *      If the memory block was moved, the returned pointer will point to this
 *      new location, the passed pointer will be set to NULL.
 *      If this function fails, the original block is left untouched (it is not
 *      freed or moved) and it will return NULL.
 *      If for some reason the memory couldn't be allocated, this function will
 *      call `exit()` and print an error message indicating the call location
 *      and the amount of memory requested.
 */
#define el_realloc(pointer, size)                                              \
    el_custom_realloc((pointer), (size), el_default_handlers())

#ifdef __cplusplus
}
#endif

#endif /* SAFE_MEMORY_H_ */
