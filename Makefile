.PHONY: all clean
all: ext4c.so

ext4c.so:
	$(MAKE) -C ext4
	cp ext4/ext4c.so .

clean:
	$(MAKE) -C ext4 clean
	rm -f ext4c.so

