ifneq ($(KERNELRELEASE),)
obj-m := my_dev.o

else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD	:=$(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -Wall -Werror -Wextra main.c

endif

clean:
	rm -rf *.o *~core.depend .*.cmd *.ko *.mod.c\
		.tmp_versions module* Module* a.out \
