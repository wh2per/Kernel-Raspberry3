#include <stdio.h>
#include <sys/fcntl.h>

void main(void){
	int fd, ret;	
	
	fd = open("/dev/simple_block_dev",O_RDWR);
	ret = write(fd, NULL, 0);
	printf("success to produce :%d\n", ret);

	close(fd);
}
