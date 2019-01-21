KDIR := ~/Desktop/dev/rpi3_linux/linux
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
PWD := $(shell pwd)

obj-m := simple_timer.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
