# pyext4

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

