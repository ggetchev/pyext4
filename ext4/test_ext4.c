//
//  main.c
//  ext4
//
//  Created by Gedeon Richter on 11/06/2020.
//  Copyright © 2020 Gedeon Richter. All rights reserved.
//

#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>

#include "ext4_module.h"

struct __attribute__((packed)) ino_min_map {
    uint64_t ino;
    uint8_t size;
    char name[1];
};

struct data_ref {
	uint64_t start;
	uint64_t length;
};

void process(uint8_t * mem, uint64_t size, const char * inpath, const char * output_filename) {
    
	// find the filename and the directory name
	uint32_t inlen = strlen(inpath);
	char * buf = (char *) malloc(inlen + 1);
	if(buf) {
		memcpy(buf, inpath, inlen);
		buf[inlen] = '\0';

		char * input_filename = strrchr(buf, '/');
		if(input_filename) {
			*input_filename = '\0'; // terminate the directory path and move the pointer 1 byte ahead
			input_filename ++;
		}
		uint32_t infile_len = strlen(input_filename);
		const char * input_directory = buf;

		ext4_init(mem, size);
		uint64_t msize = ext4_list_contents(input_directory, NULL);
		uint8_t * m = (uint8_t *) malloc(msize);
		if(m) {
			ext4_list_contents(input_directory, m);
			uint8_t * p = m;
			while(p != (m + msize)) {
				struct ino_min_map * mm = (struct ino_min_map *) p;
				if(!memcmp(mm->name, input_filename, infile_len)) {
					uint64_t msize = ext4_get_contents(mm->ino, NULL);
					uint8_t * bytes = (uint8_t *) malloc(msize);
					if(bytes) {
						if(ext4_get_contents(mm->ino, bytes)) {
							int fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
							if(fd > -1) {
								struct data_ref * dr = (struct data_ref *) bytes;
								while(dr != (struct data_ref *)(bytes + msize)) {
									write(fd, mem + dr->start, dr->length);
									dr ++;
								}
								close(fd);
							}
						}
						free(bytes);
					}
				}
				p += sizeof(uint64_t) + 1 + mm->size;
			}
			free(m);
		}
	    ext4_close();
	    free(buf);
    }
}



int main(int argc, const char * argv[]) {
    struct stat st;
    if(argc < 4) {
    	const char * n = strrchr(argv[0], '/');
    	if(n) {
    		n ++;
    	} else {
    		n = argv[0];
    	}
    	printf("Usage: %s <image file> <full_path_of_file_in_the_image> <output file>\n", n);
    	return 0;
    }

    if(!stat(argv[1], &st)) {
        uint64_t size = st.st_size;
        int f = open(argv[1], O_RDONLY);
        void * mem = mmap(NULL, size, PROT_READ, MAP_PRIVATE, f, 0);
        if(mem) {
            process(mem, size, argv[2], argv[3]);
            munmap(mem, size);
        }
    } else {
    	printf("File %s does not exist.\n", argv[1]);
    }
    return 0;
}
