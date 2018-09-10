#!/bin/bash

for file in `ls /sys/kernel/debug/fortytwo/`
do
	echo "--------start loop for $file------------"
	cat /sys/kernel/debug/fortytwo/$file

	cat file > /sys/kernel/debug/fortytwo/$file 
	cat /sys/kernel/debug/fortytwo/$file 
	echo 123 > /sys/kernel/debug/fortytwo/$file 
	cat /sys/kernel/debug/fortytwo/$file 
	echo rburger > /sys/kernel/debug/fortytwo/$file 
	cat filePage > /sys/kernel/debug/fortytwo/$file 
	cat /sys/kernel/debug/fortytwo/$file
	cat fileJiff > /sys/kernel/debug/fortytwo/$file 
	cat /sys/kernel/debug/fortytwo/$file
done
