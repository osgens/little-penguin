obj-m += main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	insmod main.ko
	lsmod | grep main

# Not necessary but suggested in subject:
# chown a+r /sys/kernel/debug/fortytwo/

clean:	uninstall
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


re: 	clean \
	all

uninstall:
	rmmod main


