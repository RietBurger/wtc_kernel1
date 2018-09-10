// SPDX-License-Identifier: GPL-2.0
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/jiffies.h>
#include <linux/mutex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rburger");
MODULE_DESCRIPTION("Debugfs Module");

#define		PAGE 4096
static		DEFINE_MUTEX(my_mutex);
static char	message[PAGE] = {0};
static short	size_of_msg;
static char	uname[8] = "rburger\n";
char		jiffholder[50];

struct dentry *my_dir;  /*use this as pointer to create files in the directory
			 *(and to clean up at the end)
			 */
struct dentry *my_jiffies;
struct dentry *my_foo;
struct dentry *my_id;

static ssize_t	id_read(struct file *filep, char *buffer, size_t len,
			loff_t *offset);
static ssize_t	id_write(struct file *filep, const char *buffer, size_t len,
			 loff_t *offset);

static int		foo_open(struct inode *inodep, struct file *filep);
static int		foo_release(struct inode *inodep, struct file *filep);
static ssize_t	foo_read(struct file *filep, char *buffer, size_t len,
			 loff_t *offset);
static ssize_t	foo_write(struct file *filep, const char *buffer, size_t len,
			  loff_t *offset);

static ssize_t	jiff_read(struct file *filep, char *buffer, size_t len,
			  loff_t *offset);

const struct file_operations fops_id = {
	.read = id_read,
	.write = id_write
};

static ssize_t	id_read(struct file *filep, char *buffer, size_t len,
			loff_t *offset)
{
	int count = 0;

	count = simple_read_from_buffer(buffer, 8, offset, uname, 8);

	if (count < 0) {
		pr_err("RED: ID - Invalid input.\n");
		return -EINVAL;
	}
	pr_info("RED: ID - read successful.\n");
	return count;
}

static ssize_t	id_write(struct file *filep, const char *buffer, size_t len,
			 loff_t *offset)
{
	int count = 0;

	if (!buffer) {
		pr_err("RED: ID Err - NULL buffer\n");
		return -EINVAL;
	} else if (len < 0 || len > 8) {
		pr_err("RED: ID Err - incorrect length\n");
		return -EINVAL;
	}

	count = simple_write_to_buffer(message, 8, offset, buffer, len);

	if (strcmp(message, uname) == 0 ||
	    strcmp(message, "rburger") == 0) {
		pr_info("RED: ID write success. Matched: %s\n", message);
		return count;
	}
	pr_err("RED: ID Err write - username doesn't match\n");
	return -EINVAL;
}

const struct file_operations fops_jiff = {
	.read = jiff_read
};

static ssize_t	jiff_read(struct file *filep, char *buffer, size_t len,
			  loff_t *offset)
{
	int count = 0;
	unsigned long tick = jiffies;
	int ret = sprintf(jiffholder, "%lu\n", tick);

	size_of_msg = strlen(jiffholder);

	if (ret > 0) {
		count = simple_read_from_buffer(buffer, PAGE, offset,
						jiffholder, size_of_msg);

		if (count < 0) {
			pr_err("RED: jiff read Err - Invalid input\n");
			return -EINVAL;
		}
		pr_info("RED: jiff read success\n");
		return count;
	}
	pr_err("RED: jiff read Err - unable to read from jiff.h\n");
	return -EINVAL;
}

const struct file_operations fops_foo = {
	.read = foo_read,
	.open = foo_open,
	.write = foo_write,
	.release = foo_release
};

static int		foo_open(struct inode *inodep, struct file *filep)
{
	if (mutex_trylock(&my_mutex) == 1) {
		pr_info("RED: Foo locking foo\n");
		return 0;
	}
	pr_err("RED: Foo already busy\n");
	return -EBUSY;
}

static ssize_t	foo_read(struct file *filep, char *buffer, size_t len,
			 loff_t *offset)
{
	int count = 0;

	count = simple_read_from_buffer(buffer, PAGE, offset, message,
					size_of_msg);

	if (count < 0) {
		pr_err("RED: Foo RD Err - Invalid input\n");
		return -EINVAL;
	}
	pr_info("RED: Foo RD success.\n");
	return count;
}

static ssize_t	foo_write(struct file *filep, const char *buffer, size_t len,
			  loff_t *offset)
{
	int count = 0;

	if (!buffer) {
		pr_err("RED: Foo Err - NULL buffer\n");
		return -EINVAL;
	} else if (len < 0 || len > PAGE) {
		pr_err("RED: Foo Err incorrect length\n");
		return -EINVAL;
	}

	//clean out file
	count = simple_write_to_buffer(message, PAGE, offset, 0, PAGE);
	count = simple_write_to_buffer(message, PAGE, offset, buffer,
				       len);
	size_of_msg = strlen(message);

	if (count > 0) {
		pr_info("RED: Foo write success.\n");
		return count;
	}
	pr_err("RED: Foo write Err - couldn't read message\n");
	return -EINVAL;
}

static int		foo_release(struct inode *inodep, struct file *filep)
{
	mutex_unlock(&my_mutex);
	pr_info("RED: Foo - unlocking foo\n");
	return 0;
}

void	create_vfs(void)
{
	my_dir = debugfs_create_dir("fortytwo", 0);
	my_jiffies = debugfs_create_file("jiffies", 0444, my_dir, 0,
					 &fops_jiff);
	my_id = debugfs_create_file("id", 0666, my_dir, 0, &fops_id);
	my_foo = debugfs_create_file("foo", 0644, my_dir, 0, &fops_foo);
}

static int __init hello_init(void)
{	create_vfs();
	pr_info("Created /fortytwo and files!\n");
	return 0;
}

static void __exit hello_cleanup(void)
{
	debugfs_remove_recursive(my_dir);
	pr_info("Removing /fortytwo and files.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

