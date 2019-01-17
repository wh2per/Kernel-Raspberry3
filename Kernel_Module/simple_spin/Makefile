KDIR := ~/Desktop/dev/rpi3_linux/linux
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
PWD := $(shell pwd)

obj-m := simple_spin.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules
	arm-linux-gnueabihf-gcc -o simple_spin_reader simple_spin_reader.c
	arm-linux-gnueabihf-gcc -o simple_spin_writer simple_spin_writer.c
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
