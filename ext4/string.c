#include <string.h>
#include <stdlib.h>

#include "string.h"


static void string_dealloc(pobject o) {
    struct string * me = (struct string *) o;
    if(me && me->size) {
        free(me->s);
    }
    free(me);
}

pstring string_create(const char * literal) {
    struct string * res = (struct string *) ObjCreate(sizeof(struct string));
    if(res) {
        res->o_.dealloc = string_dealloc;
        res->size = strlen(literal);
        res->s = (char *) malloc(res->size + 1);
        memcpy(res->s, literal, res->size);
        res->s[res->size] = 0;
    }
    return res;
}

const char * string_get_string(pstring str) {
    if(str) {
        return str->s;
    }
    return NULL;
}

unsigned long string_get_size(pstring str) {
    if(str) {
        return str->size;
    }
    return 0;
}


