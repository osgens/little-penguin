#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/mount.h>
#include <linux/seq_file.h>
#include <linux/fs_struct.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ogenser");
MODULE_DESCRIPTION("Ex 09 from 42 little_penguin project");
MODULE_VERSION("0.1");

// static int mymounts_show(struct seq_file *m, void *v) {
//         struct vfsmount *mnt;

//         seq_printf(m, "Mount Points:\n");

//         // Used by a reader to inform the reclaimer that the reader 
//         // is entering an RCU read-side critical section. It is illegal 
//         // to block while in an RCU read-side critical section, though 
//         // kernels built with CONFIG_PREEMPT_RCU can preempt RCU read-side 
//         // critical sections. Any RCU-protected data structure accessed 
//         // during an RCU read-side critical section is guaranteed to
//         //  remain unreclaimed for the full duration of that critical 
//         //  section.
//         rcu_read_lock();
//     // Loop through the mount points
// // Loop through the mount points
//     list_for_each_entry_rcu(mnt, &current->namespace->list, mnt_list) {
//         seq_printf(m, "%s\t%s\n", mnt->mnt_mountpoint->m_dentry->d_name.name,
//                    mnt->mnt_devname ? mnt->mnt_devname : "");
//     }
//     rcu_read_unlock();

//     return 0;
//     rcu_read_unlock();

//     return 0;
// }

static int mymounts_show(struct seq_file *m, void *v) {
// //     struct vfsmount *mnt;

//         struct dentry	*mnt;
//         // char		buff_entry[256] = {0};

// 	// memset(buffer, 0, BUFF_SIZE);
//     seq_printf(m, "Mount Points:\n");

//     rcu_read_lock();
// 	list_for_each_entry(mnt, &current->fs->root.mnt->mnt_root->d_subdirs, d_child)
// 	{

//     // Loop through the mount points
// //     list_for_each_entry_rcu(mnt, &vfsmounts, mnt_list) {
//         seq_printf(m, "%s\t%s\n", mnt->mnt_mountpoint->m_dentry->d_name.name,
//                    mnt->mnt_devname ? mnt->mnt_devname : "");
//     }
//     rcu_read_unlock();


    struct dentry *curdentry;
    char buf[1024];

    list_for_each_entry(curdentry, &current->fs->root.mnt->mnt_root->d_subdirs, d_child)
    {
        rcu_read_lock();
        if ( curdentry->d_flags & DCACHE_MOUNTED)
            seq_printf(m, " %s is mounted ! %s %s\n", curdentry->d_name.name, \
            curdentry->d_parent->d_name.name, dentry_path_raw(curdentry, buf, 1024));
        rcu_read_unlock();
        // struct path path;
        // char *path_string;
        // seq_path_root(current, &path);
        // path_string = dentry_path_raw(&path, "/", PAGE_SIZE);
    }
    return 0;
    return 0;
}

static int mymounts_open(struct inode *inode, struct file *file) {
        return single_open(file, mymounts_show, NULL);
        return 0;
}

static const struct proc_ops mymounts_fops = {
        .proc_open = mymounts_open,
        .proc_read = seq_read,
        .proc_lseek = seq_lseek,
        .proc_release = single_release
};

static int __init mymounts_init(void) {
    proc_create("mymounts", 0, NULL, &mymounts_fops);
    printk(KERN_INFO "mymounts module loaded.\n");
    return 0;
}

static void __exit mymounts_exit(void) {
    remove_proc_entry("mymounts", NULL);
    printk(KERN_INFO "mymounts module unloaded.\n");
}

module_init(mymounts_init);
module_exit(mymounts_exit);