ifneq ($(KERNELRELEASE),)

	obj-m := toy-usb.o

else

	KERN_DIR = /usr/src/linux-headers-$(shell uname -r)/
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules

endif

clean:
	rm -rf *.o *.ko *.cmd *.mod


