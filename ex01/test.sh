#!/bin/bash
make
# Load the kernel module
sudo insmod main.ko

# Display the last line of the kernel logs using dmesg
echo
echo "Message after loading module:"
dmesg -T | tail -1

# Unload the kernel module
sudo rmmod main.ko

# Display the last line of the kernel logs again
echo "Message after unloading module:"
dmesg -T | tail -1

# make clean
