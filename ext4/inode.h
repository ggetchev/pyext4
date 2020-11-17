#ifndef INODE_H
#define INODE_H

#include <stdint.h>
#include "object.h"

// A simple in-memory reference counted representation of the inode

struct inode {
    struct object o_;
    uint64_t ino;
    uint16_t mode;
    uint32_t flags;
    uint64_t size;
    uint64_t block_start;
};

typedef struct inode * pinode;

// Creates an inode
// Parameters: data - the disk image data
//             offset - the offset in the disk image, where the inode is
//             ino - the inode index
// Return value: the inode representation or NULL if error.
struct inode * inode_create(const uint8_t * data, uint64_t offset, uint64_t ino);


#endif // INODE_H

