#!/bin/bash
if [ "$#" != "2" ];then
    echo "Usage: $0 URL"
    exit -1
fi
echo "Broken links:"

mkdir -p /tmp/$$.link
cd /tmp/$$.link

lynx -traversal $1 > /dev/null
count=0
sort -u reject.dat > links.txt
