#ifndef SAFE_STRING_H_
#define SAFE_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * cstring
 * 
 * A convenient way to differentiate between a pointer to a single char and a
 * c-string (both have the type `char *`): use `cstring` for the latter.
 * Note that it is still a pointer and memory allocation and deallocation
 * should still be done.
 */
typedef char * cstring;

/**
 * const_cstring
 *
 * A less verbose way to declare a constant c-string. The pointer cannot be
 * changed and neither can the string to which it points.
 */
typedef const char * const const_cstring;

/**
 * cstring_array
 * A convenient way to differentiate between a pointer to a single c-string
 * and an array of multiple c-strings (both have the type `char **`, or
 * `cstring *`): use `cstring_array` for the latter.'
 */
typedef cstring * cstring_array;

#ifdef __cplusplus
}
#endif

#endif /* SAFE_STRING_H_ */
