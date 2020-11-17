#ifndef STRING_H
#define STRING_H

#include "object.h"

// A simple reference counted representation of a string.

struct string {
    struct object o_;
    char * s;
    unsigned long size;
};

typedef struct string * pstring;

//Creates a new string object from a pointer.
pstring string_create(const char * str);

// Gets the underlying string.
// Return value: NULL-terminated string.
const char * string_get_string(pstring  str);

// Get the string size in bytes, not counting the trailing NULL.
unsigned long string_get_size(pstring str);
#endif // STRING_H

