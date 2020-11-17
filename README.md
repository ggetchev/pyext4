# pyext4

## Description
This small project reads ext4 images and extracts files from them without mounting.

## How to build
```bash
make
``` 

## How to test the C part 
```bash
cd ext4
./test ./test.img /lib/libc.so ./extracted_libc.so
```

## How to test the Python part
```bash
./ext4_test.py ./test.img /lib/libc.so ./extracted_libc.so
```

## Remarks
It is obvious you must have an ext4 image.

## How to build a test ext4 image
```bash
sudo dd if=/dev/zero of=test.img bs=1M count=64
mkfs.ext4 test.img
mkdir test 
sudo mount -o loop test.img ./test 
```
Now you can go into the test directory and do whatever you want.
When you finish, just execute 
```bash
exit
```
And you have the test.img ext4 filesystem.
