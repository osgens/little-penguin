#!/bin/bash


# ###test for debug fs
# ls /sys/kernel/debug/
# ### in case of fail 
# mount -t debugfs none /sys/kernel/debug/
# ###check if enabled in kernel
# cat /boot/config-6.4.12 | grep CONFIG_DEBUG_FS

### test file creation and permissions
echo
echo "Test General:"
ls -l /sys/kernel/debug/ | grep fortytwo
ls -l /sys/kernel/debug/fortytwo
dmesg -T | tail -1

### test id
echo
echo "Test id:"
echo
cat /sys/kernel/debug/fortytwo/id
echo 
echo 'Error expected:'
echo 123 > /sys/kernel/debug/fortytwo/id
echo 'Error expected:'
echo "123nser" > /sys/kernel/debug/fortytwo/id
echo $?
echo ogenser > /sys/kernel/debug/fortytwo/id
echo $?
dmesg -T | tail -1

### test jiffies
echo
echo "Test Jiffies:"
echo
echo "My Jiffies:"
cat /sys/kernel/debug/fortytwo/jiffies
### check real jiffies
echo 'Real Jiffies:'
grep -E "^cpu|^jiff" /proc/timer_list
echo 
echo 'Error expected:'
echo 123 > /sys/kernel/debug/fortytwo/jiffies

### test foo
echo
echo "Test Foo:"
echo
whoami

echo 123 > /sys/kernel/debug/fortytwo/foo
cat /sys/kernel/debug/fortytwo/foo

### test threads
gcc testthreads.c 
./a.out 
rm a.out

# chown -R /sys/kernel/debug/fortytwo/
###in case of virgin vm
# useradd Tester
# usermod -a -G sudo Tester

###test rights
# su Tester
# echo 123 > /sys/kernel/debug/fortytwo/foo
# sudo echo 123 > /sys/kernel/debug/fortytwo/foo
# cat /sys/kernel/debug/fortytwo/foo
# sudo cat /sys/kernel/debug/fortytwo/foo