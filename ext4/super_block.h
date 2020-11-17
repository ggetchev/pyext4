#ifndef SUPER_BLOCK_H
#define SUPER_BLOCK_H

#include <stdint.h>
#include "object.h"

// A reference counted representation of a super block.

struct SuperBlock {
    struct object o_;
    uint64_t blocks_count;
    uint64_t block_size;
    uint64_t blocks_per_group;
    uint64_t block_group_size;
    uint64_t inodes_per_group;
    uint64_t cluster_size;
    uint8_t has_dir_indices;
    uint8_t sparse_super_block;
    uint8_t flexible_block_groups;
    uint64_t flex_block_size;
    uint8_t  huge_file;
    uint64_t inode_size;
    uint64_t desc_size;
    uint64_t free_inodex_count;
    uint64_t free_blocks_count;
    uint64_t feature_compat;
    uint64_t feature_incompat;
    uint64_t feature_ro_compat;
    uint16_t block_group_nr;
};

// Creates an in-memory representation of a super block, based on the super block from the disk image.
// Returns NULL on failure.
struct SuperBlock * super_block_create(const uint8_t * data, uint64_t size);



#endif // SUPER_BLOCK_H

