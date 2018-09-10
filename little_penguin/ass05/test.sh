#!/bin/bash

#aliasses
#test5
#RBR

echo "cat /dev/fortytwo"
cat /dev/fortytwo
echo "dmesg -T | tail -1"
dmesg -T | tail -1

echo "cat file > /dev/fortytwo"
cat file > /dev/fortytwo
echo "dmesg -T | tail -1"
dmesg -T | tail -1

echo "echo file > /dev/fortytwo"
echo file > /dev/fortytwo
echo "dmesg -T | tail -1"
dmesg -T | tail -1

echo "echo rburger > /dev/fortytwo"
echo rburger > /dev/fortytwo
echo "dmesg -T | tail -1"
dmesg -T | tail -1

