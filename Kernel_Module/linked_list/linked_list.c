#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/list.h>
#include <linux/slab.h>

#define DEV_NAME "linked_list_dev"

MODULE_LICENSE("GPL");

struct test_list{
	struct list_head list;
	int id;
};

struct test_list mylist;

static int __init simple_basic_kernel_init(void){
	struct test_list *tmp = 0;
	struct list_head *pos = 0;
	unsigned int i;

	printk("Init Module\n");

	INIT_LIST_HEAD(&mylist.list);		// 리스트 초기화 

	for(i=0; i<5; i++){			// 리스트에 삽입 
		tmp = (struct test_list*)kmalloc(sizeof(struct test_list),GFP_KERNEL);
		tmp->id = i;
		printk("enter to list [%d]\n", tmp->id);
		list_add(&tmp->list, &mylist.list);
	}

	i=0;

	printk("use list_for_each & list_entry\n");
	list_for_each(pos, &mylist.list){		// 리스트 순회 방법1
		tmp = list_entry(pos,struct test_list, list);
		printk("pos[%d], id[%d]\n", i, tmp->id);
		i++;
	}

	i = 0;

	printk("use list_for_each_entry\n");		
	list_for_each_entry(tmp, &mylist.list, list){	// 리스트 순회 방법2
		printk("pos[%d], id[%d]\n", i, tmp->id);
		i++;
	}

	return 0;
}

static void __exit simple_basic_kernel_exit(void){
	struct test_list *tmp = 0;
	struct list_head *pos = 0;
	struct list_head *q = 0;
	unsigned int i = 0;

	printk("Exit Module\n");
	i=0;
	list_for_each_safe(pos, q, &mylist.list){		// 삭제 방법!
		tmp = list_entry(pos, struct test_list, list);
		printk("free pos[%d], id[%d]\n", i, tmp->id);
		list_del(pos);
		kfree(tmp);
		i++;
	}
	printk("Exit Module\n");
}

module_init(simple_basic_kernel_init);
module_exit(simple_basic_kernel_exit);
