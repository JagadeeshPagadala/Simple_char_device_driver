
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>


#define BUFFERS 10000

static dev_t major;
static struct cdev char_dev;
static struct class *class;



int my_open(struct inode* inode, struct file* file)
{
	printk(KERN_EMERG"its open");
	return 0;
}

int my_close(struct inode* inode, struct file* file)
{
	printk(KERN_EMERG"its close");
	return 0;
}

ssize_t my_write(struct file* file, const  char __user *data,size_t num, loff_t* offset)
{
	int* buffer[BUFFERS];
	int i=0;
	printk(KERN_EMERG"its write");
	for(i=0;i<BUFFERS;i++)
	{
		buffer[i]=kmalloc(1024,GFP_KERNEL);
		if(!buffer[i])
		{
			printk(KERN_EMERG"\n kmalloc failed in %d allocation \n",i);
			return -ENOMEM;
		}
	}
	printk(KERN_INFO"\n kamlloc succes %d \n",i);
	return num;
}

ssize_t my_read(struct file* file, char __user *data,size_t num, loff_t* offset)
{
	printk(KERN_EMERG"its read");
	return num;
}

struct file_operations fileops=
{
	.owner=THIS_MODULE,
	.open=my_open,
	.release=my_close,
	.write=my_write,
	.read=my_read,
};
static int kmalloc_init(void)
{
	printk(KERN_EMERG"init module");
	if(alloc_chrdev_region(&major,0,2,"jk")<0)
	{
		return -1;
	}
	if((class=class_create(THIS_MODULE,"malloc_class"))==NULL)
	{
		unregister_chrdev_region(major,2);
		return -1;
	}
	cdev_init(&char_dev,&fileops);
	if(cdev_add(&char_dev,major,1)==-1)
	{
		device_destroy(class,major);
		class_destroy(class);
		unregister_chrdev_region(major,2);
		return -1;
	}
	if(device_create(class,NULL,major,NULL,"jk0")==NULL)
	{
		device_destroy(class,major);
		class_destroy(class);
		unregister_chrdev_region(major,2);
		return -1;
	}
	return 0;
}

static void kmalloc_exit(void)
{
	cdev_del(&char_dev);
	device_destroy(class,major);
	class_destroy(class);
	unregister_chrdev_region(major,2);
	printk("exit module ");
}


module_init(kmalloc_init);
module_exit(kmalloc_exit);
MODULE_AUTHOR("JAGADEESH PAGADALA");
MODULE_DESCRIPTION("A simple character device");
MODULE_LICENSE("GPL");
