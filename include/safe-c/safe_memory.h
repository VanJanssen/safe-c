#ifndef SAFE_MEMORY_H_
#define SAFE_MEMORY_H_

#include <malloc.h>

void* safe_malloc_function(size_t size, const char* calling_function);
#define safe_malloc(size) safe_malloc_function(size, __FUNCTION__);

void safe_free_function(void** pointer);
#define safe_free(pointer) safe_free_function((void **) &(pointer))

#endif /* SAFE_MEMORY_H_ */
