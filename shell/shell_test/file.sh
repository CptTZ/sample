#!/bin/bash
#author:李茂源
#email:maoyuan.li@feixun.com.cn

file="/home/lmy/shell/test.sh"
if [ -r $file ]
then
	echo "$file文件可读"
else
	echo "$file文件不可读"
fi

if [ -w $file ]
then
	echo "$file文件可写"
else
	echo "$file文件不可写"
fi

if [ -x $file ]
then
	echo "$file文件可执行"
else
	echo "$file文件不可执行"
fi

if [ -f $file ]
then
	echo "$file文件为普通文件"
else
	echo "$file文件为特殊文件"
fi

if [ -d $file ]
then
	echo "$file文件是个目录"
else
	echo "$file文件不是个目录"
fi

if [ -s $file ]
then
	echo "$file文件不为空"
else
	echo "$file文件为空"
fi

if [ -e $file ]
then
	echo "$file文件存在"
else
	echo "$file文件不存在"
fi

