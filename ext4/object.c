#include "object.h"

#include <stdlib.h>

static void object_deallocate(struct object * o) {
    free(o);
}

static long object_retain(struct object * o) {
    o->rc ++;
    return o->rc;
}

static long object_release(struct object * o) {
    -- o->rc;
    long r = o->rc;
    if(!r) {
        o->dealloc(o);
    }
    return r;
}

long ObjRetain(struct object * o) {
    if(!o) {
        return 0;
    }
    return o->retain(o);
}

long ObjRelease(struct object * o) {
    if(!o) {
        return 0;
    }
    return o->release(o);
}


pobject ObjCreate(unsigned long size) {
    struct object * o = (struct object *) malloc(size);
    if(o) {
        o->rc = 1;
        o->dealloc = object_deallocate;
        o->retain = object_retain;
        o->release = object_release;
    }
    return o;
}
