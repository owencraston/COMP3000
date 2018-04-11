// The following code was adapted from the my_pid.c example file 
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/thread_info.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Owen Craston");
MODULE_DESCRIPTION("create proc /proc/owen_clock");

static int owen_clock_open(struct inode *inode, struct file *file);
static ssize_t owen_clock_read(struct file *file, char __user *buffer, size_t count, loff_t *pos);
static int owen_clock_release(struct inode *inodep, struct file *filep);

/* Structure of file operations */
static const struct file_operations owen_clock_fops = {
 .owner = THIS_MODULE,
 .open = owen_clock_open,
 .read = owen_clock_read,
 .llseek = seq_lseek,
 .release = owen_clock_release, };

/* Called each time "/proc/owen_clock" is opened.
* inode = pointer to an inode
* file = pointer to a file
*/
static int owen_clock_open(struct inode *inode, struct file *file) {
 printk(KERN_ERR " \"owen_clock_read\" is open!\n");
 return 0;
}

/* Called when "/proc/owen_clock" is read.
* List ids of running processes.
* file = pointer to a file
* buffer = ptr to buffer to where data is put
* count = buffer length
* pos = offset in buffer
*/
static ssize_t owen_clock_read(struct file *file, char __user *buffer, size_t count, loff_t *pos)
{
    struct timeval tv;
    long secs, usecs;
    int length = 0;

    // if position in file is non zero
    if (*pos != 0)
        return 0; // no more data
    // get the time value
    do_gettimeofday(&tv);

    // store the values for seconds and microseconds
    secs = tv.tv_sec;
    usecs = tv.tv_usec;

    length += sprintf(buffer, "%lu sec %lu usec\n", secs, usecs);
    *pos = length;
    return length; 
}

/* Called when "/proc/owen_clock" is closed.
* inodep = pointer to an inode
* filep = pointer to a file
*/
static int owen_clock_release(struct inode *inodep, struct file *filep) {
 return 0;
}

/* Invoked when the module is loaded,
* entry point of a module.
*/
static int __init owen_clock_init(void) {
	// create entry "/proc/owen_clock"
	if (proc_create(
		"owen_clock", 0, NULL, &owen_clock_fops) == 0) {
		printk(KERN_ERR "Failed to register\n");
		return -ENOMEM;
	}
	return 0;
}

/* Invoked when the module is unloaded,
* unregistration with the kernel
*/
static void __exit owen_clock_cleanup(void) {
 // remove directory entry by name
 remove_proc_entry("owen_clock", NULL);
}

module_init(owen_clock_init);
module_exit(owen_clock_cleanup);