#include <stdlib.h>

#include "fs_entity.h"

static const char * fs_entity_str_types[LAST] = {
  "unknown", "file", "directory", "character device", "block device", "fifo", "socket", "symbolic link"
};

static void fs_entity_dealloc(pobject o) {
    struct fs_entity * me = (struct fs_entity *) o;
    if(me) {
        RELEASE(me->name);
        RELEASE(me->children);
        RELEASE(me->links_to);
        RELEASE(me->data_refs);
        free(me);
    }
}

struct fs_entity * create_entity(uint64_t ino, const char * name, enum fs_entity_type type, struct fs_entity * parent) {
    struct fs_entity * me = (struct fs_entity *) ObjCreate(sizeof(struct fs_entity));
    if(me) {
        me->_o.dealloc = fs_entity_dealloc;
        me->ino = ino;
        me->name = string_create(name);
        me->type = type;
        me->parent = parent;
        me->children = list_create();
        me->data_refs = list_create();
        me->links_to = NULL;
        me->data_length = 0;
    }
    return me;
}

const char * fs_entity_get_type(pobject o) {
    struct fs_entity * fe = (struct fs_entity *) o;
    if(fe->type < LAST) {
    	return fs_entity_str_types[fe->type];
    }
    return fs_entity_str_types[UNKNOWN];
}

