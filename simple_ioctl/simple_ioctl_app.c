#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

#define DEV_NAME "simple_ioctl_dev"

#define IOCTL_START_NUM 0x80
#define IOCTL_NUM1 IOCTL_START_NUM+1
#define IOCTL_NUM2 IOCTL_START_NUM+2
#define IOCTL_NUM3 IOCTL_START_NUM+3

#define SIMPLE_IOCTL_NUM 'z'
#define SIMPLE_IOCTL1 _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define SIMPLE_IOCTL2 _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM2, unsigned long *)
#define SIMPLE_IOCTL3 _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM3, unsigned long *)

void main(void){
	int dev;
	unsigned long value = 0;
	
	dev = open("/dev/simple_ioctl_dev", O_RDWR);

	ioctl(dev,SIMPLE_IOCTL1, &value);
	ioctl(dev,SIMPLE_IOCTL2, &value);
	ioctl(dev,SIMPLE_IOCTL3, &value);

	close(dev);
}
