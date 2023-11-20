#include <linux/fs.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ogenser");
MODULE_DESCRIPTION("Task 06 from 42 little-penguin project");
MODULE_VERSION("0.1");

#define STUDENT_LOGIN "ogenser"
#define STUDENT_LOGIN_LEN 7

static struct mutex mutex_foo;
static char foo_data[PAGE_SIZE]; // Buffer for "foo" file

static ssize_t id_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
        //pr_info("Read function called");
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

static ssize_t id_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) {
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

static ssize_t jiffies_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
        char buffer[20]; // Buffer to hold the string representation of jiffies
        int len;

        if (*pos != 0) {
                return 0;  // End of file
        }

        len = snprintf(buffer, sizeof(buffer), "%lu\n", jiffies);

        if (copy_to_user(buf, buffer, len)) {
                return -EFAULT;  // Bad address
        }

        *pos += len;
        return len;
}

static ssize_t foo_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
    
        ssize_t ret = 0;

        ret = mutex_lock_interruptible(&mutex_foo);
        if (ret)
		return ret;

        if (*pos >= PAGE_SIZE) {
                mutex_unlock(&mutex_foo);
                return 0;  // End of file
        }

        if (*pos + count > PAGE_SIZE) {
                count = PAGE_SIZE - *pos;
        }

        if (copy_to_user(buf, foo_data + *pos, count)) {
                mutex_unlock(&mutex_foo);
                return -EFAULT;  // Bad address
        }

        *pos += count;
        ret = count;
        mutex_unlock(&mutex_foo);
        return ret;
}

static ssize_t foo_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) {
        ssize_t ret = 0;
        ret = mutex_lock_interruptible(&mutex_foo);
        if (ret)
		return ret;

        if (*pos >= PAGE_SIZE) {
                mutex_unlock(&mutex_foo);
                return -ENOSPC;  // No space left on device
        }

        if (*pos + count > PAGE_SIZE) {
                count = PAGE_SIZE - *pos;
        }

        if (copy_from_user(foo_data + *pos, buf, count)) {
                mutex_unlock(&mutex_foo);
                return -EFAULT;  // Bad address
        }

        *pos += count;
        ret = count;

        mutex_unlock(&mutex_foo);
        return ret;
}

static const struct file_operations id_fops = {
        .owner = THIS_MODULE,
        .read = id_read,
        .write = id_write,
};

static const struct file_operations jiffies_fops = {
        .owner = THIS_MODULE,
        .read = jiffies_read,
};

static const struct file_operations foo_fops = {
        .owner = THIS_MODULE,
        .read = foo_read,
        .write = foo_write,
};

static struct dentry *fortytwo_dir;

static int __init ex07_init(void) {
        fortytwo_dir = debugfs_create_dir("fortytwo", NULL);

        if (!fortytwo_dir) {
                pr_err("Failed to create debugfs directory\n");
                return -ENOMEM;
        }

        debugfs_create_file("id", 0666, fortytwo_dir, NULL, &id_fops);
        debugfs_create_file("jiffies", 0444, fortytwo_dir, NULL, &jiffies_fops);
        mutex_init(&mutex_foo);
        debugfs_create_file("foo", 0644, fortytwo_dir, NULL, &foo_fops);

        pr_info("Module loaded\n");
        return 0;
}

static void __exit ex07_exit(void) {
        debugfs_remove_recursive(fortytwo_dir);
        pr_info("Module unloaded\n");
}

module_init(ex07_init);
module_exit(ex07_exit);