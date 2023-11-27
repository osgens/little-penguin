#!/bin/bash

echo
echo "Message after loading module:"
dmesg -T | tail -1

udevadm control --reload-rules
udevadm trigger --action=add --sysname-match="event*"

dmesg -T | tail -5

# #view uevent in kernel
# udevadm monitor --kernel

# https://nihaal.me/post/ec5/