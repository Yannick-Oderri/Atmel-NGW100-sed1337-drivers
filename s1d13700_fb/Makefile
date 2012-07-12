# Makefile:
ARCH := avr32
CROSS_COMPILE := /home/ynki9/Desktop/buildroot/output/staging/usr/bin/avr32-linux-
KDIR := /home/ynki9/Desktop/buildroot/output/build/linux-2.6.35.4
PWD := $(shell pwd)

obj-m := s1d13700_fb_o.o

s1d13700_fb_o-y = s1d13700_fb.o

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	cp *.ko /srv/nfs/proto

default_:
	$(MAKE) INSTALL_MOD_PATH=/srv/nfs -C $(KDIR) SUBDIRS=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules_install

clean:
	rm -rf *.ko *.o* testmodule.mod* .testmodule* .tmp* Module*