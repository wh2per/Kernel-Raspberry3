KDIR := ~/Desktop/dev/rpi3_linux/linux
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
PWD := $(shell pwd)

obj-m := simple_block.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules
	arm-linux-gnueabihf-gcc -o simple_block_reader simple_block_reader.c
	arm-linux-gnueabihf-gcc -o simple_block_writer simple_block_writer.c
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
