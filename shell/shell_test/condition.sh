#!/bin/bash

if test "1" -eq "0"
then
	echo "you are right!"
else
	echo "you are wrong!"
fi

if [ $(ps -ef | grep -c "ssh") -gt 1 ]; then echo "more than one"; fi


a=10
b=20
if [ $a -eq $b ]
then
	echo "a eq b"
elif [ $a -gt $b ]
then
	echo "a great than b"
else
	echo "a less than b"
fi

for loop in 1 2 3 4 5
do
	echo "we now at $loop"
done

i=0
while test $i -lt 5
do
	echo "tile $i not ok!"
	i=$[ $i + 1 ]
done


int=1
while [ $int -lt 5 ]
do
	echo $int
	let "int++"
done

int=1
while (( $int<=5 ))
do
	echo $int
	let "int++"
done

aa(){
echo "prese <ctrl+d> exit"
while read -p "you know how weak you are:" film
do
	echo "yes!$film is a good film!\n"
done


echo ""
i=0
until [ $i -gt 6 ] 
do
	echo "until $i"
	let "i=i+1"
	sleep 1
done


echo "输入1到4之间的数字："
read -p "你输入的数字为：" num
case $num in
	1) echo "you choose 1 $num"
		;;
	2) echo "you choose 2 $num"
		;;
	3) echo "you choose 3 $num"
		;;
	4) echo "you choose 4 $num"
		;;
	5) echo "you choose 5 $num"
		;;
	*) echo "not match $num"
		;;
esac
}


while :
do
	echo -n "输入1到5之间的数字！"
	read -p "输入一个数字：" num 
	case $num in
		1|2|3|4|5) echo "your input is $num"
			;;
		*) echo "your input is wrong $num, game over!"
			break;;
	esac
done
	
while :
do
	echo -n "输入1到5之间的数字！"
	read -p "输入一个数字：" num 
	case $num in
		1|2|3|4|5) echo "your input is $num"
			;;
		*) echo "your input is wrong $num!"
			continue
			echo "game over!"
			;;
	esac
done
