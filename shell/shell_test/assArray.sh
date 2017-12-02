#!/bin/bash
declare -A assArray
assArray=([lucy]=beijing [pangzi]=shagnhai)
echo ${assArray[lucy]}
assArray[aixi]=meibanfa
echo ${assArray[aixi]}
echo ${!assArray[@]}
echo ${!assArray[*]}
for key in ${!assArray[@]}
do
           echo "$key:${assArray[$key]}"
done
