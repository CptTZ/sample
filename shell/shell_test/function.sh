#!/bin/bash
#author:heihei
#url:maoyuan.li@phicomm.com
myfun()
{
	echo "This is my first function!"
}

echo "---func start---"
myfun
echo "---func end---"

echo "func2 start"
funret()
{
	echo "This func is add two input"
	read -p "The first input:" num1
	read -p "The second input:" num2
	echo "The two input is $num1 $num2"
	return $((num1+num2))
}
#funret
echo "func2 end with ret:$?"


funpara()
{
	echo "The first parameter is:$1"
	echo "The second parameter is:$2"
	echo "The third parameter is:$3"
	echo "The number of parameter is:$#"
	echo "The assemble of parameter is:$*"
	echo "The assemble2 of parameter is:$@"
	echo "The config is:$-"
}

echo "***go funcpara***"
funpara 1 32312 324324 asfd asf jlasdjf asdf
echo "*** func para end ***"
