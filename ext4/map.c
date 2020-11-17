#include "map.h"
#include "khash.h"



KHASH_MAP_INIT_INT64(int64_pobject_map, pobject)

struct map {
    struct object o_;
    khash_t(int64_pobject_map) * map;
};

static void map_dealloc(pobject o) {
    struct map * m = (struct map *) o;
    if(m) {
        pobject obj;
        uint64_t key;
        kh_foreach(m->map, key, obj, ObjRelease(obj); kh_val(m->map, __i) = NULL;)
        kh_destroy(int64_pobject_map, m->map);
        free(m);
    }
}


struct map * map_create(void) {
    struct map * m = (struct map *) ObjCreate(sizeof(struct map));
    if(m) {
        m->o_.dealloc = map_dealloc;
        m->map = kh_init(int64_pobject_map);
    }
    return m;
}

void map_insert(struct map * map, uint64_t key, pobject value) {
    if(map) {
        int r;
        int k = kh_put(int64_pobject_map, map->map, key, &r);
        if(!r) {
            pobject obj = kh_value(map->map, k);
            ObjRelease(obj);
        }
        kh_value(map->map, k) = value;
        ObjRetain(value);
    }
}

pobject map_get(struct map * map, uint64_t key) {
    if(map) {
        int k = kh_get(int64_pobject_map, map->map, key);
        if(k == kh_end(map->map)) {
            return NULL;
        }
        return kh_value(map->map, k);
    }
    return NULL;
}

void map_remove_key(struct map * map, uint64_t key) {
    if(map) {
        int k = kh_get(int64_pobject_map, map->map, key);
        pobject obj = kh_value(map->map, k);
        ObjRelease(obj);
        kh_del(int64_pobject_map, map->map, k);
    }
}

void map_iterate(struct map * map, iteration_cb cb, void * ctx) {
    if(map) {
        uint64_t key;
        pobject obj;
        kh_foreach(map->map, key, obj, if(cb(ctx, key, obj)) break; );
    }
}
