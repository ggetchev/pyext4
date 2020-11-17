#!/usr/bin/env python3

#
# /* The MIT License
#
#    Copyright (c) 2020 by ggetchev
#
#    Permission is hereby granted, free of charge, to any person obtaining
#    a copy of this software and associated documentation files (the
#    "Software"), to deal in the Software without restriction, including
#    without limitation the rights to use, copy, modify, merge, publish,
#    distribute, sublicense, and/or sell copies of the Software, and to
#    permit persons to whom the Software is furnished to do so, subject to
#    the following conditions:
#
#    The above copyright notice and this permission notice shall be
#    included in all copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
#    BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
#    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
#    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#    SOFTWARE.
# */

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




