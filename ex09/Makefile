obj-m += main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	insmod main.ko
	lsmod | grep main

clean:	uninstall
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


re: 	clean \
	all

uninstall:
	rmmod main


