#include "ext4_module.h"

#include "fs.h"

static fsref fs = (fsref) 0;

void ext4_init(const uint8_t * data, uint64_t data_size) {
    if(!fs) {
        fs = fs_create(data, data_size);
    }
}

void ext4_close(void) {
    if(fs) {
        fs_destroy(fs);
        fs = 0;
    }
}

uint64_t ext4_list_contents(const char * path, uint8_t * outdata) {
    if(fs) {
        return fs_list_contents(fs, path, outdata);
    }
    return 0;
}

uint64_t ext4_get_contents(uint64_t ino, uint8_t * outdata) {
    if(fs) {
        return fs_get_contents(fs, ino, outdata);
    }
    return 0;
}

