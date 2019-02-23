# Raspberry-Pi-3

## Kernel Module
- [x] export_var
- [x] linked_list
- [x] blocking I/O
- [x] character device driver
- [x] printk
- [x] ioctl
- [x] spinlock
- [x] kernel timer

## Sensor Module
- [x] LED
- [x] wiring LED
- [x] PIR
- [x] timer with LED
- [x] wiring LCD

### 1. How to make Makefile
      obj-m := module_code.o
      KDIR := ~/Desktop/dev/rpi3_linux/linux
      
      default:
          make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C$(KDIR) M=$(shell pwd) modules
      clean:
          make -C$(KDIR) M=$(shell pwd) clean
          
### 2. How to make mknod.sh
      MODULE = "module_dev"
      MAJOR=$(awk "\$2==\"$MODULE\" {print \$1}" /proc/devices)
      
      mknod /dev/$MODULE c $MAJOR 0

### 3. How to Cross Compile
      $ arm-linux-gnueabif-gcc -o module_code_app module_code_app.c

### 4. How to Run
      $ sudo insmod module.ko
      $ sudo sh mknod.sh
      $ ./module_code_app

### 5. How to Quit
      $ sudo rmmod module.ko
      $ rm /dev/module_dev
      
