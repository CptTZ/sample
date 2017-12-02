#!/bin/bash
#author:李茂源
#email:maoyuan.li@feixun.com.cn

a=10
b=20

if [[ $a -lt 100 && $b -gt 100 ]]
then
	echo "$a -lt 100 && $b -gt 100, 返回 true"
else
	echo "$a -lt 100 && $b -gt 100, 返回 false"
fi

if [[ $a -lt 100 || $b -gt 100 ]]
then
	echo "$a -lt 100 || $b -gt 100, 返回 true"
else
	echo "$a -lt 100 || $b -gt 100, 返回 false"
fi


if [ $a -lt 100 -a $b -gt 100 ]
then
	echo "$a -lt 100 && $b -gt 100, 返回 true"
else
	echo "$a -lt 100 && $b -gt 100, 返回 false"
fi

if [ $a -lt 100 -o $b -gt 100 ]
then
	echo "$a -lt 100 || $b -gt 100, 返回 true"
else
	echo "$a -lt 100 || $b -gt 100, 返回 false"
fi
