
#include "data.h"
#include <string.h>
#include <stdlib.h>

static void data_dealloc(pobject o) {
    struct data * d = (struct data *) o;
    if(d) {
        if(d->m) {
            free(d->m);
        }
        free(d);
    }
}

struct data * data_create(void * mem, uint64_t length) {
    if(mem && length) {
        struct data * d = (struct data *) ObjCreate(sizeof(struct data));
        if(d) {
            d->o_.dealloc = data_dealloc;
            d->len = length;
            d->m = (uint8_t *) malloc(length);
            if(d->m) {
                memcpy(d->m, mem, length);
                return d;
            }
            free(d);
        }
    }
    return NULL;
}

