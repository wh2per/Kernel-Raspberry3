#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
#define LED1 5
#define LED2 6
#define LED3 13
#define DEV_NAME "timer_led_dev"

static struct timer_list my_timer;

static void my_timer_func(unsigned long data){
	printk("simple_timer : %ld\n", data);
	
	if(my_timer.data%3==1){
		gpio_set_value(LED1, 1);
		gpio_set_value(LED2, 0);
		gpio_set_value(LED3, 0);
	}else if(my_timer.data%3==2){
		gpio_set_value(LED1, 0);
		gpio_set_value(LED2, 1);
		gpio_set_value(LED3, 0);
	}else if(my_timer.data%3==0){
		gpio_set_value(LED1, 0);
		gpio_set_value(LED2, 0);
		gpio_set_value(LED3, 1);
	}

	my_timer.data = data+1;
	my_timer.expires = jiffies + (2*HZ);

	add_timer(&my_timer);
}

static int timer_led_open(struct inode *inode, struct file* file){
	printk("timer_led open\n");
	
	// timer init
	init_timer(&my_timer);

	my_timer.function = my_timer_func;
	my_timer.data = 1L;
	my_timer.expires = jiffies + (2*HZ);
	add_timer(&my_timer);
	
	// led init
	gpio_request_one(LED1, GPIOF_OUT_INIT_LOW, "LED1");
	gpio_request_one(LED2, GPIOF_OUT_INIT_LOW, "LED2");
	gpio_request_one(LED3, GPIOF_OUT_INIT_LOW, "LED3");

	return 0;
}

static int timer_led_release(struct inode *inode, struct file* file){
	printk("timer_led close\n");
	
	del_timer(&my_timer);

	gpio_free(LED1);
	gpio_free(LED2);
	gpio_free(LED3);
	
	return 0;
}

struct file_operations timer_led_fops = {
	.open = timer_led_open,
	.release = timer_led_release,
};

static dev_t dev_num;
static struct cdev *cd_cdev;

static int __init timer_led_init(void){
	printk("Hi TimerLED!\n");
	
	// device driver init
	alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &timer_led_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
	return 0;
}

static void __exit timer_led_exit(void){
	printk("Bye TimerLED!\n");
	
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
}
module_init(timer_led_init);
module_exit(timer_led_exit);

