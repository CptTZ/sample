#!/bin/bash
# filename: filestat.sh
if [ $# -ne 1 ]
then
    echo $0 basepath;
    echo
    exit 0
fi
path=$1

declare -a statarray;
declare -a numarray;

while read line;
do
    has_find=0
    otype=0
    ftype=`file -b "$line"`
    #echo $ftype
    #echo ${#statarray[@]}
    while [[ "$otype" -lt "${#statarray[@]}" ]]
    do
        if [[ "${statarray[$otype]}" = "$ftype" ]]; then
                has_find=1
                let numarray[$otype]++
                break;
        fi
        let otype++
    done
    if [[ "$has_find" == "0" ]]; then
        statarray[$otype]=${ftype}
        let numarray[$otype]++
    fi
done< <(find $path -type f -print)

#echo =========== File types and counts ===========
otype=0
while [[ "$otype" -lt "${#statarray[@]}" ]]
do
        echo ${statarray[$otype]} : ${numarray[$otype]}
        let otype++
done
