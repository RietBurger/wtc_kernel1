// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/printk.h>
//#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rburger");
MODULE_DESCRIPTION("Load USB Module");

//static struct usb_driver skel_driver = {
//	name: "my_usb_mod",
//	probe: skel_probe,
//	disconnect: skel_disconnect,
//	fops = &skel_fops,
//	minor = USB_SKEL_MINOR_BASE,
//	id_table = skel_table,
//};

static int __init usb_load(void)
{
//	int ret = 0;

//	ret = usb_register(&skel_driver);
	pr_info("USB: usb loaded\n");
	return 0;
}

static void __exit usb_unload(void)
{
//	usb_deregister(&skel_driver);
	pr_info("USB: usb unloaded\n");
}

module_init(usb_load);
module_exit(usb_unload);
