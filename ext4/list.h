#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include "object.h"


// A reference counted wrapper of the 'klist'.
// 'klist' is a very simple list implementation, see klist.h for more details.

struct list;
typedef struct list * plist;

// Creates a list object.
// Return value: the list object or NULL if error.
struct list * list_create(void);

// Appends an object to the list.
// Parameters: lst - the list itself.
//             obj - a reference counted object to be added to the list.
void list_append(struct list * lst, pobject obj);

// Returns an iterator to the list's head.
// Parameters: lst - the list object itself.
// Return value: an iterator to the begin of the list (the head).
void * list_begin(struct list *  lst);

// Returns an iterator to the list's tail.
// Parameters: lst - the list object itself.
// Return value: an iterator to the end of the list (the tail).
void * list_end(struct list * lst);

// Moves forward the iterator, returns the next iterator or NULL if end is reached.
// Parameters: it - the iterator itself.
// Return value: the next iterator or NULL if the end is reached.
void * list_next(void * it);

// Returns the underlying object from the iterator or NULL if error.
// Parameters: it - the iterator itself.
// Return value: pointer to the underlying object. The object is of type 'object' so a cast is necessary to access the actual data.
pobject list_access(void * it);

// Returns the underlying object from a list, by given index or NULL if error.
// Parameters: lst - the list itself.
//             index - the index inside the list (as if the list is an array)
// Return value: pointer to the underlying object. The object is of type 'object' so a cast is necessary to access the actual data.
pobject list_at(struct list * lst, int index);

// Returns the list size in elements or 0 if error.
// Parameters: lst - the list itself.
// Return value: the size of the list in elements. Returns 0 if the list is empty OR if the 'lst' points to a NULL pointer.
uint64_t list_size(struct list * lst);

#endif // LIST_H

