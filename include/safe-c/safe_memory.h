#ifndef SAFE_MEMORY_H_
#define SAFE_MEMORY_H_

#include <malloc.h>

void* safe_malloc_function(size_t size, const char* calling_function);

#endif /* SAFE_MEMORY_H_ */
