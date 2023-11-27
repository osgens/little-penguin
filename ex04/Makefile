obj-m += main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	cp usbkeyboardload.rules /etc/udev/rules.d/
	# sudo udevadm control --reload-rules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

re: 	clean \
	all



