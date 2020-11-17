#ifndef FS_H
#define FS_H

#include <stdint.h>
#include "object.h"

// An in-memory representation of the ext4 filesystem.

typedef struct FS * fsref;


// Creates the filesystem object from data from the disk image.
// Parameters: data - a pointer to the disk image data.
//             data_size - the length of the 'data'.
// Return values: pointer to the filesystem object or NULL if error.
// After done with the filesystem object - call 'fs_destroy()' to clean it up.
fsref fs_create(const uint8_t * data, uint64_t data_size);

// Destroys the filesystem object.
// Parameters: fs - the filesystem object itself.
void fs_destroy(fsref fs);

// Lists the contents of a path, with all directories and files into it.
// !! Does not get the nested directories or files. !!
// Parameters: fs - the filesystem object itself
//             path - a path, that should be valid for the image (e.g. '/lib64/libm.so')
//             outdata - a pointer to a writable memory; if 'outdata' is NULL the function returns the size of the needed memory.
//             The 'outdata' is a contiguous area, populated with the following structure:
//             struct __attribute__((packed)) ino_min_map {
//                                   uint64_t ino;        // the inode of the object (directory, file, etc)
//                                   uint8_t size;        // size of the next field, 'name'
//                                   char name[1];        // the name of the object (directory, file, etc)
//                                };
// Return value: the size of the memory needed for the contents to be stored or 0 if error.
uint64_t fs_list_contents(fsref fs, const char * path, uint8_t * outdata);

// Gets the origin and length of the actual data.
// Parameters: fs - the filesystem object itself
//             ino - the inode for which we want the data to be retrieved
//             outdata - a pointer to a writable memory; if 'outdata' is NULL the function returns the size of the needed memory.
//             The 'outdata' is a contiguous area, populated with the following structure:
//             struct DataRef {
//                    uint64_t start; // offset within the image, from where the data chunk starts
//                    uint64_t length; // the length of the data chunk
//             };
// Return value: the total size in bytes of the object, represented by the 'ino' or 0 if error.
uint64_t fs_get_contents(fsref fs, uint64_t ino, uint8_t * outdata);

#endif // FS_H

