#ifndef BLOCK_GROUP_DESC_H
#define BLOCK_GROUP_DESC_H

#include <stdint.h>
#include "object.h"

// A reference counted representation of a block group descriptor

struct BlockGroupDescriptor {
    struct object o_;
    uint64_t bg_block_bitmap;
    uint64_t bg_inode_bitmap;
    uint64_t bg_inode_table;
    uint64_t bg_itable_unused;
    uint64_t bg_free_blocks_count;
    uint64_t bg_used_dirs_count;
    uint64_t bg_exclude_bitmap;
    uint64_t bg_block_bitmap_csum;
    uint64_t bg_inode_bitmap_csum;
    uint64_t bg_free_inodes_count;
    uint8_t my_size;
};

// Creates an in-memory representation of a block group descriptor, based on the block group descriptor from the disk image.
// Returns NULL on failure.

struct BlockGroupDescriptor * block_group_descriptor_create(const uint8_t * data, uint64_t size, uint16_t desc_size);

#endif // BLOCK_GROUP_DESC_H
