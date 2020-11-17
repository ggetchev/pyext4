.PHONY: all clean
all:: ext4c.so test clear

CC = clang
CFLAGS = -O0 -g -fPIC
LDFLAGS =

SRCS = block_group_desc.c ext4_module.c fs_entity.c list.c map.c super_block.c data.c fs.c inode.c object.c string.c


ext4c.so: $(addsuffix _ext4.o,$(basename $(SRCS)))
	$(CC) -o $@ -shared $^ $(LDFLAGS)

%_ext4.o: %.c ext4.h object.h %.h
	$(CC) -o $@ -c $< $(CFLAGS)

test: test_ext4.o $(addsuffix _ext4.o,$(basename $(SRCS)))
	$(CC) -o $@ $^ $(LDFLAGS)

test_ext4.o: test_ext4.c ext4_module.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *.so test

clear:
	rm -f *.o