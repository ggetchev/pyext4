
   # The MIT License
   #
   # Copyright (c) 2020 by ggetchev
   #
   # Permission is hereby granted, free of charge, to any person obtaining
   # a copy of this software and associated documentation files (the
   # "Software"), to deal in the Software without restriction, including
   # without limitation the rights to use, copy, modify, merge, publish,
   # distribute, sublicense, and/or sell copies of the Software, and to
   # permit persons to whom the Software is furnished to do so, subject to
   # the following conditions:
   #
   # The above copyright notice and this permission notice shall be
   # included in all copies or substantial portions of the Software.
   #
   # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   # EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   # MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   # NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   # BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   # ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   # CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   # SOFTWARE.


import ctypes
import struct
import os 

class Ext4:
    __ext4 = ctypes.CDLL(os.path.join(os.path.dirname(__file__), "ext4c.so"))

    def __init__(self, data):
        self._init = None
        self._close = None
        self._list_contents = None
        self._get_contents = None
        self.in_data = bytes(data)

    def __enter__(self):
        self._init = getattr(Ext4.__ext4, "ext4_init")
        self._init.argtypes = [ctypes.c_char_p, ctypes.c_uint64]

        self._close = getattr(Ext4.__ext4, "ext4_close")

        self._list_contents = getattr(Ext4.__ext4, "ext4_list_contents")
        self._list_contents.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
        self._list_contents.restype = ctypes.c_uint64

        self._get_contents = getattr(Ext4.__ext4, "ext4_get_contents")
        self._get_contents.argtypes = [ctypes.c_uint64, ctypes.c_char_p]
        self._get_contents.restype = ctypes.c_uint64

        inp = ctypes.c_char_p(self.in_data)
        insize = ctypes.c_uint64(len(self.in_data))
        self._init(inp, insize)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self._close()
        self._init = None
        self._close = None
        self._list_contents = None
        self._get_contents = None
        self.in_data = None

    def list_contents(self, path):
        ret = []
        cpath = ctypes.c_char_p(path.encode("ascii"))
        size = self._list_contents(cpath, None)
        if size == 0:
            return ret
        opath = ctypes.create_string_buffer(size)
        self._list_contents(cpath, opath)
        raw = opath.raw
        p = 0
        while p < size:
            ino, sz = struct.unpack("<QB", raw[p:p+9])
            p += 9
            name = raw[p:p+sz].decode("ascii")
            p += sz
            ret.append((ino, name))
        return ret

    def get_contents(self, ino):
        ret = []
        ii = ctypes.c_uint64(ino)
        size = self._get_contents(ii, None)
        output = ctypes.create_string_buffer(size)
        self._get_contents(ii, output)
        raw = output.raw
        p = 0
        while p < size:
            offset, length = struct.unpack("<QQ", raw[p:p+16])
            ret.append((offset, length))
            p += 16
        return ret









