// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ogenser");
MODULE_DESCRIPTION("Ex 04 from 42 little_penguin project");
MODULE_VERSION("0.1");

// Initialization function called when the module is loaded
static int __init ex04_init(void)
{
	// printk prints messages to the kernel log
	printk(KERN_INFO "USB Hello world !\n");
	return 0; // 0 indicates success
}

// Cleanup function called when the module is unloaded
static void __exit ex04_exit(void)
{
	printk(KERN_INFO "USB Cleaning up module.\n");
}

// Registering the initialization and exit functions
module_init(ex04_init);
module_exit(ex04_exit);
