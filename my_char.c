// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) Steve Jeong <steve@how2flow.net>
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>

#define DRIVER_NAME "my_char"
#define NUM_DEVICES 1

static dev_t device_num;
static struct cdev cdev;

static int my_char_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "my_char_open\n");
	return 0;
}

static int my_char_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "my_char release\n");
	return 0;
}

static struct file_operations my_char_fops = {
	.owner = THIS_MODULE,
	.open = my_char_open,
	.release = my_char_release,
};

static int __init my_char_init(void)
{
	int ret;

	// register character device
	ret = alloc_chrdev_region(&device_num, 0, NUM_DEVICES, DRIVER_NAME);
	if (ret < 0) {
		printk(KERN_ERR "Failed to allocate device number\n");
		return ret;
	}

	// character device init
	cdev_init(&cdev, &my_char_fops);
	cdev.owner = THIS_MODULE;

	// add character device (cdev_init() -> cdev_add())
	ret = cdev_add(&cdev, device_num, NUM_DEVICES);
	if (ret < 0) {
		unregister_chrdev_region(device_num, NUM_DEVICES);
		printk(KERN_ERR "Failed to add device to the system\n");
		return ret;
	}

	printk(KERN_INFO "my_char driver initialized\n");
	return 0;
}

static void __exit my_char_exit(void)
{
	// unregister character device (cdev_del() -> unregister_chrdev_region())
	cdev_del(&cdev);
	unregister_chrdev_region(device_num, NUM_DEVICES);
	printk(KERN_INFO "my_char driver removed\n");
}

module_init(my_char_init);
module_exit(my_char_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Steve Jeong");
MODULE_DESCRIPTION("A simple character device driver example");
