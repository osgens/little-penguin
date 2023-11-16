#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ogenser");
MODULE_DESCRIPTION("Ex 01 from 42 little=penguin project");
MODULE_VERSION("0.1");

// Initialization function called when the module is loaded
static int __init hello_init(void) {
    // printk prints messages to the kernel log
    printk(KERN_INFO "Hello, World!\n");
    return 0; // 0 indicates success
}

// Cleanup function called when the module is unloaded
static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

// Registering the initialization and exit functions
module_init(hello_init);
module_exit(hello_exit);
