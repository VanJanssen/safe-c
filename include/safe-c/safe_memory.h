#ifndef SAFE_MEMORY_H_
#define SAFE_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/**
 * Memory allocation with strict boundary and error checking.
 *
 * @param size
 *      The size in bytes to be allocated. Be aware that size in an unsigned
 *      type, passing signed values can lead to conversion errors.
 *      If `size == 0`, this function will call `exit()` and print an error
 *      message indicating which function requested zero memory. You should set
 *      your pointer to NULL yourself explicitly if you want a pointer without
 *      memory allocation.
 *
 * @param calling_function
 *      The name of the function calling this function. You can pass a
 *      custom NULL termination string, or pass the __FUNCTION__ define. You
 *      can use the macro function `safe_malloc(size)`, which will automatically
 *      pass the __FUNCTION__ define as second parameter. This usage is the most
 *      convenient because calling it will be the same as `malloc`.
 *
 * @return
 *      The return value will be a pointer to the allocated memory, the memory
 *      will be initialized to all zero.
 *      If for some reason the memory couldn't be allocated, this function will
 *      call `exit()` and print an error message indicating the caller function
 *      and the amount of memory request.
 */
void* safe_malloc_function(const size_t size, const char* calling_function);

#define safe_malloc(size) safe_malloc_function(size, __FUNCTION__);

/**
 * Frees previously allocated memory and sets the passed pointer to NULL.
 *
 * This function requires an address the a pointer, the macro function
 * `safe_free` can be used to call this function with the pointer itself, so
 * usage is the same as that of `free()`. The macro calls this function with
 * the address of the passed pointer and the proper cast.
 *
 * @param pointer_address
 *      The address of the pointer that shall be freed.
 *      If `pointer_address == 0`, nothing is done.
 */
void safe_free_function(void** pointer_address);

#define safe_free(pointer) safe_free_function((void**) &(pointer))

/**
* Memory reallocation with strict boundary and error checking.
*
* @param pointer_address
*      The address of the pointer pointing to the memory block to be reallocated.
*      This function changes the size of this memory block to `size` bytes. The
*      contents will be unchanged in the range from the start of the region up
*      to the minimum of the old and the new size.
*      If `pointer_address == NULL`, this function will call `exit()` and print
*      an error message containing the caller function.
*      Unless the value pointed to be `pointer_address` is NULL, it must be a
*      valid pointer returned by an earlier call to a memory (re)allocation
*      function.
*      To make it easier to call this function, the macro function
*      `safe_realloc(pointer, size)` can be used. This macro function takes the
*      address of the pointer, which makes calling it the same as calling
*      `realloc`.
*
* @param size
*      The new size in bytes to for the memory block pointed to by `pointer`.
*      Be aware that size in an unsigned type, passing signed values can lead
*      to conversion errors.
*      If `size == 0`, this function will free the pointer and then call `exit()`
*      and print an error message indicating which function requested zero
*      memory. You should set your pointer to NULL yourself explicitly if you
*      want a pointer without memory allocation.
*      If the new size is larger than the old size, the added memory will
*      _not_ be initialized.
*
* @param calling_function
*      The name of the function calling this function. You can pass a
*      custom NULL termination string, or pass the __FUNCTION__ define. You
*      can use the macro function `safe_malloc(size)`, which will automatically
*      pass the __FUNCTION__ define as second parameter. This usage is the most
*      convenient because calling it will be the same as `realloc`.
*
* @return
*      The return value will be a pointer to the reallocated memory.
*      If the new size is larger than the old size, the added memory will _not_
*      be initialized.
*      If the memory block was moved, this pointer points to the new block and
*      the previous pointer is freed and set to NULL. Otherwise this pointer
*      is the same pointer as before.
*      If for some reason the memory couldn't be reallocated, this function will
*      call `exit()` and print an error message indicating the caller function
*      and the amount of memory request.
*/
void* safe_realloc_function(void** pointer_address, const size_t size,
        const char* calling_function);

#define safe_realloc(pointer, size) safe_realloc_function((void**) &(pointer), size, __FUNCTION__)

#ifdef __cplusplus
}
#endif

#endif /* SAFE_MEMORY_H_ */
