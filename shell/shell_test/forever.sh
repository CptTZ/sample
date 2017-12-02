#!/bin/bash
i=0
#while :
#do
#	echo "forever one:$i"
#	i=$[ $i + 1 ]
#	sleep 1
#done

#while true
#do
#	echo "forever two:$i"
#	i=$[ $i + 1 ]
#	sleep 1
#done

for ((;;))
do
	echo "forever three:$i"
	i=$[ $i + 1 ]
	sleep 1
done
