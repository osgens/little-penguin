obj-m += lol.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	insmod lol.ko
	lsmod | grep lol

clean:	uninstall
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


re: 	clean \
	all

uninstall:
	rmmod lol


