#ifndef OBJECT_H
#define OBJECT_H

// A reference counted object representation.
// Note: The object is not thread safe!

struct object {
    long rc;
    long (*retain)(struct object *);
    long (*release)(struct object *);
    void (*dealloc)(struct object *);
};

typedef struct object * pobject;

pobject ObjCreate(unsigned long size);

long ObjRetain(struct object * o);
long ObjRelease(struct object * o);

#define OBJ(x) ((struct object *) (x))

// Macros for convenience

#define RETAIN(x) ObjRetain(OBJ(x))
#define RELEASE(x) ObjRelease(OBJ(x))

#endif // OBJECT_H

