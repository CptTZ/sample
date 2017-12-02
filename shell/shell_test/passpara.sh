#!/bin/bash
# author:李茂源
# url:mail.phicomm.com

echo "Shell 传递参数示例！";
echo "文件名：$0";
echo "参数个数：$#";
echo "单字符串显示所有参数：$*"
echo "引号显示所有参数：$@"
echo "后台运行的当前进程的ID号：$$"
echo "后台运行的最后一个进程的ID号：$!"
echo "参数1：$1";
echo "参数2：$2";
echo "参数3：$3";
echo "参数4：$4";
echo "选项:$-";

echo "-- \$* 演示 --"
for i in "$*";
do
	echo $i
done

echo "-- \$@ 演示 --"
for i in "$@";
do
	echo $i
done

sleep 100
