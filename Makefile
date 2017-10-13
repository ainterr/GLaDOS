obj-m += GLaDOS.o

all:
	make -C song
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	make clean -C song

install:
	cp GLaDOS.ko /lib/modules/`uname -r`/kernel/drivers/pci
	echo GLaDOS >> /etc/modules
	depmod
	insmod GLaDOS.ko
