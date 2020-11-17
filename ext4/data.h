#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include "object.h"

// A simple "data" representation.
// "Data" means block of memory, characterized by a pointer and length.
// Currently, the "data" objects are copy-on-write (e.g. no move operations are supported).

struct data {
    struct object o_;
    uint8_t * m;
    uint64_t len;
};

// Creates a new data object.
// Copies the contents of 'mem' into it.

struct data * data_create(void * mem, uint64_t length);


#endif

