#!/bin/bash
array_var=(1 2 3 4 5 6)
for i in 1 2 3 4 5 6
do
	echo "${array_var[i]}"
done

array_var[0]="test1"
array_var[1]="test2"
array_var[2]="test3"
array_var[3]="test4"
array_var[4]="test5"
array_var[5]="test6"
for i in 1 2 3 4 5 6
do
	echo "${array_var[$i]}"
done

echo ${array_var[*]}
echo ${array_var[@]}
echo ${#array_var[*]}
echo ${!array_var[*]}
