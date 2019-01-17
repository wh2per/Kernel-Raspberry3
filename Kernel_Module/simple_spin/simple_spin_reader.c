#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include "simple_spin.h"

int main(void){
	int dev;
	struct str_st user_str;

	dev = open(DEV_NAME, O_RDWR);
	ioctl(dev, SIMPLE_SPIN_READ, &user_str);
	
	printf("%s\n", user_str.str);

	close(dev);
}