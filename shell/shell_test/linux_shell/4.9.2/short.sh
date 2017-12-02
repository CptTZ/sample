#!/bin/bash
if [ $# != 1 ]; then
        echo "Usage:$0 javascript"
fi

cat $1 | tr -d '\n\t' | tr -s ' ' \
| sed 's/ \?\([(){};,:"]\) \?/\1/g'  \
| sed 's:/\*.*\*/::g'
