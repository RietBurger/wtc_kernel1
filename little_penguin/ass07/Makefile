ifneq ($(KERNELRELEASE),)
	obj-m := my_mod.o

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD	:=$(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc main.c
	insmod my_mod.ko
	chmod 755 /sys/kernel/debug/
	chmod 755 /sys/kernel/debug/fortytwo/

endif

clean:
	rm -rf *.o *~core.depend .*.cmd *.ko *.mod.c\
		.tmp_versions module* Module*  \
		a.out \
