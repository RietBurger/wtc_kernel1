// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/page.h>
#include <linux/mutex.h>

// Dont have a license, LOL
MODULE_LICENSE("GPL");
MODULE_AUTHOR("rburger");
MODULE_DESCRIPTION("String reverse");

char	str[PAGE_SIZE];
char	tmp[PAGE_SIZE];
static	DEFINE_MUTEX(my_mutex);

static int		myfd_open(struct inode *inode, struct file *filep);
static int		myfd_release(struct inode *inode, struct file *filep);
static ssize_t	myfd_read(struct file *fp, char *user, size_t size,
			  loff_t *offs);
static ssize_t	myfd_write(struct file *fp, const char *user, size_t size,
			   loff_t *offs);

const struct file_operations myfd_fops = {
	.open = &myfd_open,
	.read = &myfd_read,
	.write = &myfd_write,
	.release = &myfd_release
};

static struct miscdevice myfd_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "reverse",
	.fops = &myfd_fops
};

static int __init myfd_init(void)
{
	int retval;

	pr_info("RED: FD initializing device\n");
	retval = misc_register(&myfd_device);
	if (retval)
		return retval;
	pr_info("RED: FD got minor: %i\n", myfd_device.minor);
	return 0;
}

static void __exit myfd_cleanup(void)
{
	pr_info("RED: FD cleanup myfd\n");
	misc_deregister(&myfd_device);
}

ssize_t myfd_read(struct file *fp, char *user, size_t size, loff_t *offs)
{
	ssize_t ret;
	size_t len;
	int loop;

	len = strlen(str);
	loop = 0;
	while (len > 0) {
		tmp[loop++] = str[len - 1];
		len--;
	}
	tmp[loop] = 0x0;

	pr_info("RED: FD this is tmp in read: %s\n", tmp);
	ret = simple_read_from_buffer(user, size, offs, tmp, loop);
	if (ret >= 0) {
		pr_info("RED: FD read successful. this is user: %s\n", user);
		return ret;
	}
	pr_err("RED: FD read failed\n");
	return -EINVAL;
}

ssize_t myfd_write(struct file *fp, const char *user, size_t size, loff_t *offs)
{
	ssize_t res;

	res = 0;
	//clean out buffer
	res = simple_write_to_buffer(str, PAGE_SIZE, offs, 0, PAGE_SIZE);
	res = simple_write_to_buffer(str, size, offs, user, size);
	str[size + 1] = 0x0;
	if (res > 0) {
		pr_info("RED: FD write success. this is in str: %s\n", str);
		return res;
	}
	pr_err("RED: FD write failed\n");
	return -EINVAL;
}

static int		myfd_open(struct inode *inodep, struct file *filep)
{
	if (mutex_trylock(&my_mutex) == 1) {
		pr_info("RED: FD locking myfd\n");
		return 0;
	}
	pr_err("RED: FD already busy\n");
	return -EBUSY;
}

static int		myfd_release(struct inode *inodep, struct file *filep)
{
	mutex_unlock(&my_mutex);
	pr_info("RED: FD unloking myfd\n");
	return 0;
}

module_init(myfd_init);
module_exit(myfd_cleanup);

