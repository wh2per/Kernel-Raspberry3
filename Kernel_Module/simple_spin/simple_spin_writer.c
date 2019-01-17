#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include "simple_spin.h"

int main(void){
	int dev;
	struct str_st user_str = {
		"Reader : hi, writer!", 0
	};

	user_str.len = strlen(user_str.str);
	
	printf("Writer : hello, reader!!!\n");

	dev = open(DEV_NAME, O_RDWR);
	ioctl(dev, SIMPLE_SPIN_WRITE, &user_str);

	close(dev);
}
