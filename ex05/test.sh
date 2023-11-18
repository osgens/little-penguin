#!/bin/sh
cat /dev/fortytwo
echo 
echo 123 > /dev/fortytwo 
echo "123nser" > /dev/fortytwo
echo $?
echo ogenser > /dev/fortytwo
echo $?
dmesg -T | tail -10