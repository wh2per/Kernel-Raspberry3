#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <asm/delay.h>

MODULE_LICENSE("GPL");

#include "simple_spin.h"

spinlock_t my_lock;
struct str_st *kern_buf;

void delay(int sec){
	int i,j;
	for(j=0; j<sec; j++){
		for(i=0; i<1000; i++){
			udelay(1000);
		}
	}
}

static int simple_spin_read(struct str_st *buf){
	int ret;
	printk("delay before");
	delay(5);
	printk("delay after");
	spin_lock(&my_lock);
	// 임계영역 
	ret = copy_to_user(buf, kern_buf, sizeof(struct str_st));	// kern_buf -> buf
	memset(kern_buf, '\0', sizeof(struct str_st));
	//
	spin_unlock(&my_lock);	

	return ret;
}	

static int simple_spin_write(struct str_st *buf){
	int ret;
	
	spin_lock(&my_lock);
	// 임계영역 
	ret = copy_from_user(kern_buf, buf, sizeof(struct str_st));	// buf -> kern_buf
	//
	spin_unlock(&my_lock);

	return ret;
}	

static long spin_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	struct str_st *user_buf;
	int ret;
	
	user_buf = (struct str_st*)arg;
	
	switch(cmd){
		case SIMPLE_SPIN_READ:
			ret = simple_spin_read(user_buf);
			printk("simple_spin_read: %d\n",ret);
			break;
		case SIMPLE_SPIN_WRITE:
			ret = simple_spin_write(user_buf);
			printk("simple_spin_write: %d\n",ret);
			break;
	}	

	return 0;
}


static int simple_spin_open(struct inode *inode, struct file *file){
	printk("simple_spin open\n");
	return 0;
}

static int simple_spin_release(struct inode *inode, struct file *file){
	printk("simple_spin release\n");
	return 0;
}

struct file_operations simple_spin_fops ={
	.unlocked_ioctl = spin_ioctl,
	.release = simple_spin_release,
	.open = simple_spin_open,
	
};

static dev_t dev_num;
static struct cdev *cd_cdev;

static int __init simple_spin_init(void){
	int ret;
	printk("Init Module\n");

	// char device driver 영역 할당 
	alloc_chrdev_region(&dev_num, 0,1,DEV_NAME);
	cd_cdev = cdev_alloc();
	// char device 추가 
	ret = cdev_add(cd_cdev,dev_num,1);
	if(ret<0){
		printk("fail to add character device\n");
		return -1;
	}
	
	// kern_buf 메모리 할당 
	kern_buf = (struct str_st*)kmalloc(sizeof(struct str_st), GFP_KERNEL);
	memset(kern_buf, '\0', sizeof(struct str_st));
	
	return 0;
}

static void __exit simple_spin_exit(void){
	printk("Exit module\n");
	// char device 삭제 
	cdev_del(cd_cdev);
	// char device driver 영역 해제 
	unregister_chrdev_region(dev_num,1);

	// kern_buf 메모리 해제 
	kfree(kern_buf);
}

module_init(simple_spin_init);
module_exit(simple_spin_exit);
