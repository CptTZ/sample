#!/bin/bash
if [ $# != 1 ];then
        print "Usage:$0 short_sh\n"
fi

cat $1 | sed 's/\([{;]\)/\1\n/g' \
    | sed 's/}/\n}/g'
