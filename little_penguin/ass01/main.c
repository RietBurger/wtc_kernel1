// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rburger");
MODULE_DESCRIPTION("Hello World Module");

static int __init hello_init(void)
{
	pr_info("Hello world!\n");
	return 0;
}

static void __exit hello_cleanup(void)
{
	pr_info("Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
