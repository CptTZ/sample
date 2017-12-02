#!/bin/bash

array_name=(val0 val1 val2 val3 "val4")

array_name[5]=val5

echo ${array_name[@]}
for i in 0 1 2 3 4 5 6
do
	echo ${array_name[i]}
done

i=0
while [ $i -le 6 ]
do
	echo ${array_name[i]}
	i=`expr $i + 1`
	echo $i
	sleep 1
done


#length
echo "length of array ${#array_name[@]}"
echo "length of array ${#array_name[*]}"
echo "length of array ${#array_name[2]}"
