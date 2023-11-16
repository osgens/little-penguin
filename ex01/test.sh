#!/bin/bash

# Load the kernel module
sudo insmod main.ko

# Display the last line of the kernel logs using dmesg
echo "[ $(date)] Message after loading module:"
dmesg | tail -1

# Unload the kernel module
sudo rmmod main.ko

# Display the last line of the kernel logs again
echo "[ $(date)] Message after unloading module:"
dmesg | tail -1
