#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ogenser");
MODULE_DESCRIPTION("Ex 05 from 42 little-penguin project");
MODULE_VERSION("0.2");

#define STUDENT_LOGIN "ogenser"
#define STUDENT_LOGIN_LEN 7

static ssize_t ex05_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
        pr_info("Read function called");
        // Check if already at the end of the file
        if (*pos != 0) {
            return 0;  // End of file
        }

        // Copy the student login to the user buffer
        if (copy_to_user(buf, STUDENT_LOGIN, strlen(STUDENT_LOGIN))) {
            return -EFAULT;  // Bad address
        }

        // Update the position and return the length of the login
        *pos += strlen(STUDENT_LOGIN);
        return strlen(STUDENT_LOGIN);
}

static ssize_t ex05_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) {
	char temp[STUDENT_LOGIN_LEN];
        pr_info("Write function called");
        //check input lenght // Copy 9 bytes from user // Check if the written value matches the student login
	if ((count != STUDENT_LOGIN_LEN+1) ||            
		(copy_from_user(temp, buf, STUDENT_LOGIN_LEN)) ||
		(strncmp(temp, STUDENT_LOGIN, STUDENT_LOGIN_LEN)))
	        return -EINVAL;
	else
	  return count;
}

static const struct file_operations ex05_fops = {
        .owner = THIS_MODULE,
        .read = ex05_read,
        .write = ex05_write,
};

static struct miscdevice ex05_misc_device = {
        .name = "fortytwo",
        //allocate static minor number
        .minor = MISC_DYNAMIC_MINOR,
        //const struct file_operations *fops :
        // To allow custom file operations like read and write
        .fops = &ex05_fops,
};

static int __init ex05_init(void) {
        int ret;

        ret = misc_register(&ex05_misc_device);
        if (ret) {
            pr_err("Failed to register misc device\n");
            return ret;
        }

        pr_info("Module loaded\n");
        return 0;
}

static void __exit ex05_exit(void) {
        misc_deregister(&ex05_misc_device);
        pr_info("Module unloaded\n");
}

module_init(ex05_init);
module_exit(ex05_exit);