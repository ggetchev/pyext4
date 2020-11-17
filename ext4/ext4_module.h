#ifndef EXT4_MODULE_H
#define EXT4_MODULE_H

#include <stdint.h>

// A simple ext4 module representation.


// Initializes the ext4 module
// Parameters: data - a pointer to the ext4 image data
//             data_size - the size of the image data
// When finished, the user must call ext4_close()
// Currently one module can work with one image only.
// Parallel work with images is currently not supported.
void ext4_init(const uint8_t * data, uint64_t data_size);

// Cleans up the ext4 module structures
void ext4_close(void);

// Lists the contents of a path, with all directories and files into it.
// !! Does not get the nested directories or files. !!
// Parameters: path - a path, that should be valid for the image (e.g. '/lib64/libm.so')
//             outdata - a pointer to a writable memory; if 'outdata' is NULL the function returns the size of the needed memory.
//             The 'outdata' is a contiguous area, populated with the following structure:
//             struct __attribute__((packed)) ino_min_map {
//                                   uint64_t ino;        // the inode of the object (directory, file, etc)
//                                   uint8_t size;        // size of the next field, 'name'
//                                   char name[1];        // the name of the object (directory, file, etc)
//                                };
// Return value: the size of the memory needed for the contents to be stored or 0 if error.
uint64_t ext4_list_contents(const char * path, uint8_t * outdata);



// Gets the origin and length of the actual data.
// Parameters: ino - the inode for which we want the data to be retrieved
//             outdata - a pointer to a writable memory; if 'outdata' is NULL the function returns the size of the needed memory.
//             The 'outdata' is a contiguous area, populated with the following structure:
//             struct DataRef {
//                    uint64_t start; // offset within the image, from where the data chunk starts
//                    uint64_t length; // the length of the data chunk
//             };
// Return value: the total size in bytes of the object, represented by the 'ino' or 0 if error.
uint64_t ext4_get_contents(uint64_t ino, uint8_t * outdata);

#endif // EXT4_MODULE_H


