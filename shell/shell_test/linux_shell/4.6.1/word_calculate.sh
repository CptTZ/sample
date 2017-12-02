#!/bin/bash

declare -A word_calculate

for i in `cat student_data.txt`
do
    let word_calculate[$i]++
done

#echo ${!word_calculate[@]}
for i in ${!word_calculate[@]}
do
        echo "$i time:${word_calculate[$i]}"
done
