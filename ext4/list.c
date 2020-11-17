#include "list.h"
#include "klist.h"

#include <stdlib.h>


static void do_free(void *);

static void my_free(void * ptr) {
    do_free(ptr);
}


KLIST_INIT(pobject_list, pobject, my_free)

struct list {
    struct object o_;
    klist_t(pobject_list) * lst;
    uint64_t size;
};

static void do_free(void * ptr) {
    kliter_t(pobject_list) * p = (kliter_t(pobject_list) *) ptr;
    pobject obj = kl_val(p);
    if(obj) {
        ObjRelease(obj);
    }
}


static void list_dealloc(pobject o) {
    struct list * me = (struct list *) o;
    if(me) {
        kl_destroy(pobject_list, me->lst);
        free(me);
    }
}

struct list *  list_create(void) {
    struct list * lst = (struct list *) ObjCreate(sizeof(struct list));
    if(lst) {
        lst->lst = kl_init(pobject_list);
        lst->o_.dealloc = list_dealloc;
        lst->size = 0;
    }
    return lst;
}

void list_append(struct list * lst, pobject obj) {
    *kl_pushp(pobject_list, lst->lst) = obj;
    ObjRetain(obj);
    lst->size ++;
}

void * list_begin(struct list * lst) {
    return kl_begin(lst->lst);
}

void * list_end(struct list * lst) {
    return kl_end(lst->lst);
}

void * list_next(void * it) {
    kliter_t(pobject_list) * i = (kliter_t(pobject_list)*) it;
    return kl_next(i);
}

pobject list_access(void * it) {
    kliter_t(pobject_list) * i = (kliter_t(pobject_list)*) it;
    return kl_val(i);
}

uint64_t list_size(struct list * lst) {
    if(lst) {
        return lst->size;
    }
    return 0;
}

pobject list_at(struct list * lst, int index) {
    kliter_t(pobject_list) * it;
    int c = 0;
    for(it = kl_begin(lst->lst); it != kl_end(lst->lst); it = kl_next(it)) {
        if(c == index) {
            return kl_val(it);
        }
        ++ c;
    }
    return NULL;
}


