#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ogenser");
MODULE_DESCRIPTION("Ex 01 from 42 little_penguin project");
MODULE_VERSION("0.1");

// Initialization function called when the module is loaded
static int __init ex01_init(void) {
    // printk prints messages to the kernel log
    printk(KERN_INFO "Hello world !\n");
    return 0; // 0 indicates success
}

// Cleanup function called when the module is unloaded
static void __exit ex01_exit(void) {
    printk(KERN_INFO "Cleaning up module.\n");
}

// Registering the initialization and exit functions
module_init(ex01_init);
module_exit(ex01_exit);
