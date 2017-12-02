#!/bin/bash
if [[ "$#" -lt "1" ]]
then
        echo "Usage:$0 path!"
        exit 0
fi

declare -A arr

while read LINE
do
        aa=$(file -b $LINE)
        let arr["$aa"]++
done< <(find $1 -type f)

#echo ${#arr[*]}


for index in "${!arr[@]}"
do
#        echo $index
        echo "$index : ${arr["$index"]}"
done

