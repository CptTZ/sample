#!/bin/bash
if [ $# != 1 ]
then
        echo "Usage:$0 file"
        exit 1
fi

declare -A arr

filename=$1

egrep -o "\b[[:alnum:]]+\b" $filename | \
awk '{ arr[$0]++ }
END{ printf("%-14s%s\n", "Word", "Count") ;
for(ind in arr)
        { printf("%-14s%d\n", ind, arr[ind]); }
}'
