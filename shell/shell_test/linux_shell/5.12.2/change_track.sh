#!/bin/bash
#change_track.sh
#跟踪网页跟新
if [ $# != 1 ];then
        echo "Usage: $0 URL"
        exit -1
fi

first_time=0

if [ ! -e "last.html" ];then
        first_time=1
fi

curl -silent $1 -o recent.html
if [ "$first_time" == "0" ];then
    changes=$(diff -u recent.html last.html)
    if [ -n "$changes" ];then
        echo -e "Change:\n"
        echo "$changes"
    else
        echo -e "no changes!\n"
    fi
else
    echo "[First run] Archiving .."
fi
cp recent.html last.html
