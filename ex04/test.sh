#!/bin/bash

#check not loaded
lsmod
echo


udevadm control --reload-rules

#simulate add keyboard
udevadm trigger --action=add --sysname-match="event*"
sleep 5
#check loaded
echo
lsmod
echo
sleep 5
echo "Message after loading module:"
dmesg -T | tail -1

udevadm trigger --action=remove --sysname-match="event*"
sleep 5
echo
lsmod
dmesg -T | tail -2
# #view uevent in kernel
# udevadm monitor --kernel

# https://nihaal.me/post/ec5/