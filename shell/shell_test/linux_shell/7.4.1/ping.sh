#!/bin/bash
ping $1 -c 1 -W 2 > /dev/null
if [ "$?" == "0" ]
then
        echo "ping success"
else
        echo "ping error"
fi
