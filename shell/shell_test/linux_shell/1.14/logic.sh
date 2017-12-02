#!/bin/bash
str1=aaa
if [[ -n $str1 ]] && [[ -z $str2 ]]
then
	echo str1:$str1,str2:$str2
else
	echo not ok
fi

var=0
if [ $var -eq 0 ]; then echo "True"; fi

if test $var -eq 0; then echo "True"; fi
