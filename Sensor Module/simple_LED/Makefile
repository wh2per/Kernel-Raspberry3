obj-m := simple_LED.o
KDIR := ~/Desktop/dev/rpi3_linux/linux

default:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C$(KDIR) M=$(shell pwd) modules
clean:
	make -C$(KDIR) M=$(shell pwd) clean
