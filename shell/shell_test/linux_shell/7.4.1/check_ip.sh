#!/bin/bash

bb=${1%.*}
bb=${bb}"."
for aa in ${bb}{1..255}
do
    ping $aa -c 1 -W 1 > /dev/null
    if [ "$?" == "0" ]; then
        echo "$aa alive"
    fi
done
