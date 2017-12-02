#!/bin/sh

#number: -eq -ne -gt -ge -lt -le
num1=100
num2=100
if test $num1 -eq $num2
then
	echo "two numbers equal"
else
	echo "two numbers not equal"
fi

#string = != -z -n
str1="nihao"
str2="hehe"
if test 
then
	echo "two string equal!"
else
	echo "two string not equal!"
fi

#file -e -r -w -x -s -d -f -c -b
cd /bin
if test -e ./bash
then
	echo "file exist!"
else
	echo "file not exitst!"
fi

#logic ! -a -o
cd /bin
if test -e ./notfile -o -e ./bash
then
	echo "at leset one file exist!"
else
	echo "two file not exist"
fi
###
