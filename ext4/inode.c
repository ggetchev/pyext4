#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "inode.h"
#include "ext4.h"



static void inode_dealloc(pobject o) {
    struct inode * me = (struct inode *) o;
    if(me) {
        free(me);
    }
}

struct inode * inode_create(const uint8_t * data, uint64_t offset, uint64_t ino) {
    struct inode * self = (struct inode *) ObjCreate(sizeof(struct inode));
    if(self) {
        self->o_.dealloc = inode_dealloc;
        struct ext4_inode * nd = (struct ext4_inode *) (data + offset);
        self->ino = ino;
        self->flags = nd->i_flags;
        self->mode = nd->i_mode;
        self->block_start = offset + offsetof(struct ext4_inode, i_block);
        self->size = ((uint64_t) nd->i_size_high << 32) | nd->i_size_lo;
    }
    return self;
}

