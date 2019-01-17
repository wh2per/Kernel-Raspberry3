#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/cdev.h>
MODULE_LICENSE("GPL");

#define DEV_NAME "simple_ioctl_dev"

#define IOCTL_START_NUM 0x80
#define IOCTL_NUM1 IOCTL_START_NUM+1
#define IOCTL_NUM2 IOCTL_START_NUM+2
#define IOCTL_NUM3 IOCTL_START_NUM+3

#define SIMPLE_IOCTL_NUM 'z'
#define SIMPLE_IOCTL1 _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM1, unsigned long *)
#define SIMPLE_IOCTL2 _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM2, unsigned long *)
#define SIMPLE_IOCTL3 _IOWR(SIMPLE_IOCTL_NUM, IOCTL_NUM3, unsigned long *)

static long simple_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
	switch(cmd){
	case SIMPLE_IOCTL1:
		printk("simple_ioctl 1\n");
		break;
	case SIMPLE_IOCTL2:
		printk("simple_ioctl 2\n");
		break;
	case SIMPLE_IOCTL3:
		printk("simple_ioctl 3\n");
		break;
	default:
		return -1;
	}

	return 0;
}

static int simple_ioctl_open(struct inode *inode, struct file *file){
	printk("simple_ioctl open\n");
	return 0;
}

static int simple_ioctl_release(struct inode *inode, struct file *file){
	printk("simple_ioctl release\n");
	return 0;
}

struct file_operations simple_char_fops =
{
	.unlocked_ioctl = simple_ioctl,
	.open = simple_ioctl_open,
	.release = simple_ioctl_release,
};

static dev_t dev_num;
static struct cdev *cd_cdev;

static int __init simple_ioctl_init(void){
	printk("Init Module\n");

	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &simple_char_fops);
	cdev_add(cd_cdev, dev_num, 1);

	return 0;
}

static void __exit simple_ioctl_exit(void){
	printk("Exit Module\n");
	
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
}

module_init(simple_ioctl_init);
module_exit(simple_ioctl_exit);
