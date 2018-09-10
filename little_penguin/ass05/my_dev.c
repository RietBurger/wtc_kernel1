// SPDX-License-Identifier: GPL-2.0
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/printk.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rburger");
MODULE_DESCRIPTION("Misc Character Driver");

//declare global variables here
static char	message[8] = {0};
static char	uname[8] = "rburger\n";

static ssize_t	dev_read(struct file *filep, char *buffer, size_t len,
			 loff_t *offset);
static ssize_t	dev_write(struct file *filep, const char *buffer,
			  size_t len, loff_t *offset);

static struct miscdevice my_dev;

const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = dev_read,
	.write = dev_write
};

int __init create_minor(void)
{
	int retval;

	pr_info("RBR: initializing 42");
	my_dev.minor = MISC_DYNAMIC_MINOR;
	my_dev.name = "fortytwo";
	my_dev.fops = &fops;
	retval = misc_register(&my_dev);

	if (retval)
		return retval;
	pr_info("RBR: got minor: %i\n", my_dev.minor);
	return 0;
}

static void __exit destroy_minor(void)
{
	misc_deregister(&my_dev);
	pr_info("RBR: cleaning up module\n");
}

static ssize_t		dev_read(struct file *filep, char *buffer, size_t len,
				 loff_t *offset)
{
	int count = 0;

	//buffer sent in is 'receive' in main.
	count = simple_read_from_buffer(buffer, 8, offset, uname, 8);

	if (count < 0) {
		pr_info("RBR: Invalid input\n");
		return -EINVAL;
	}
	pr_info("RBR: read successful\n");
	return count;
}

static ssize_t		dev_write(struct file *filep, const char *buffer,
				  size_t len, loff_t *offset)
{
	int count = 0;

	if (!buffer) {
		pr_info("RBR: NULL buffer\n");
		return -EINVAL;
	} else if (len < 0 || len > 8) {
		pr_info("RBR: incorrect length\n");
		return -EINVAL;
	}

	/* message declared above to read into. here buffer is input
	 * from av[1].
	 */
	count = simple_write_to_buffer(message, 8, offset, buffer, len);

	if (strcmp(message, uname) == 0 ||
	    strcmp(message, "rburger") == 0) {
		pr_info("RBR: username matched: %s\n", message);
		return count;
	}
	pr_info("RBR: username doesn't match\n");
	return -EINVAL;
}

module_init(create_minor);
module_exit(destroy_minor);
