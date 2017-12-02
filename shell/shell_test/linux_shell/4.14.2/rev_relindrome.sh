#!/bin/bash
if [[ "$1" == "$(echo $1 | rev)" ]];then
        echo "rev relindrome"
else
        echo "rev not relindrome"
fi
