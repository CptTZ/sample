#!/bin/bash
echo -e "line1 f2 f3\nline2 f4 f5\nline3 f6 f7" | \
awk '{
print "Line no;"NR",No of fields:"NF,"$0="$0, "$NF="$NF,"$(NF-1)="$(NF-1),"$(NF-2)="$(NF-2)
} END{print NR}'
#if [ $# != 1 ]
#then
#        echo "Usage: $0 file"
#fi
#awk 'BEGIN{print "start"} {print} END{print "end"}' $1
