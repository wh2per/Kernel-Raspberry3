#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPU");
MODULE_AUTHOR("rpi3_linux");

static int __init hello_init(void){

	printk(KERN_NOTICE "Hello, World \n");
	return 0;
}

static void __exit hello_exit(void){

	printk(KERN_NOTICE "Goodbye\n");

}

module_init(hello_init);
module_exit(hello_exit);
