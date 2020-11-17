#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include "object.h"

// A simple reference counted wrapper around the 'khash'.
// 'Khash' is a simple hash implementation.

struct map;
typedef struct map * pmap;


// Creates a map.
// Return value: the map object or NULL if error.
struct map * map_create(void);

// Inserts a reference counted object with key into the map.
// Parameters: map - the map itself.
//             key - the key.
//             value - the object to be inserted.
void map_insert(struct map * map, uint64_t key, pobject value);

// Returns the value, corresponding to a key from the map.
// Parameters: map - the map itself.
//             key - the key, whose value has to be returned.
// Return value: the object, stored with the key. The object has to be casted to the appropriate structure to get the actual data.
// Returns NULL on missing key or on error.
pobject map_get(struct map * map, uint64_t key);

// Removes the key-value pair associated with the given key.
// Parameters: map - the map object
//             key - the key whose value has to be removed.
void map_remove_key(struct map * map, uint64_t key);

// A prototype for the map iteration callback
// Parameters: void * - a pointer to an user defined data structure
//             uint64_t - the key from the key-value pair
//             pobject - a pointer to an 'object' type of object. Must be cast to get the appropriate data structure.
// Return value: uint8_t, treated as a boolean; if the callback returns TRUE the iteration stops.
typedef uint8_t (*iteration_cb)(void *, uint64_t, pobject);

// Iterates over the map, invoking a callback for every key-value pair.
// Parameters: map - the map itself.
//             cb - the callback - see the 'iteration_cb' prototype.
//             ctx - user supplied pointer to work with 'iteration_cb' callback
void map_iterate(struct map * map, iteration_cb cb, void * ctx);

#endif // MAP_H

