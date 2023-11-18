#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ogenser");
MODULE_DESCRIPTION("Ex 04 from 42 little_penguin project");
MODULE_VERSION("0.1");

// Define USB device IDs for USB keyboard
static struct usb_device_id usb_kbd_id_table[] = {
    { USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT, USB_INTERFACE_PROTOCOL_KEYBOARD) },
    {} // Terminating entry
};

MODULE_DEVICE_TABLE(usb, usb_kbd_id_table);

// Probe function called when a USB keyboard is plugged in
static int ex04_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "USB Keyboard Plugged In\n");
    // Perform actions when the USB keyboard is plugged in
    return 0;
}

// Disconnect function called when a USB keyboard is unplugged
static void ex04_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "USB Keyboard Unplugged\n");
    // Perform actions when the USB keyboard is unplugged
}

// Define the USB driver structure
static struct usb_driver ex04_driver = {
    .name = "usb_keyboard_driver",      // Unique name for the USB driver
    .id_table = usb_kbd_id_table,       // USB device ID table
    .probe = ex04_probe,                // Probe function
    .disconnect = ex04_disconnect,      // Disconnect function
};

// Initialization function called when the module is loaded
static int __init ex04_init(void)
{
    int result = 0;
    
    printk(KERN_INFO "Hello world!\n");

    // Register the USB driver
    result = usb_register(&ex04_driver);
    if (result)
    {
        printk(KERN_ERR "usb_register failed. Error number %d\n", result);
        return result;
    }

    return 0;
}

// Cleanup function called when the module is unloaded
static void __exit ex04_exit(void)
{
    // Unregister the USB driver
    usb_deregister(&ex04_driver);
    
    printk(KERN_INFO "Cleaning up module.\n");
}

// Register the initialization and exit functions
module_init(ex04_init);
module_exit(ex04_exit);