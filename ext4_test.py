#!/usr/bin/env python3

import sys
import mmap
import os
import ext4

if len(sys.argv) < 4:
    print("Usage: {} <image file> <full_path_of_file_in_the_image> <output file>".format(sys.argv[0]))
    sys.exit(0)

img_file, target_file, output_file = sys.argv[1:4]

indir = os.path.dirname(target_file)
infile = os.path.basename(target_file)
with open(img_file, "rb") as f:
    with mmap.mmap(f.fileno(), 0, prot=mmap.PROT_READ, flags=mmap.MAP_PRIVATE) as mm:
        with ext4.Ext4(mm) as e4:
            contents = e4.list_contents(indir)
            for ino, name in contents:
                if name == infile:
                    data = e4.get_contents(ino)
                    with open(output_file, "wb") as of:
                        for start, length in data:
                            of.write(mm[start:start+length])

sys.exit(0)




