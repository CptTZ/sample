#!/bin/bash
#文件名：define.sh
#用途：一个Google定义的前端工具
limit=0
if [ ! $# -ge 1 ];
then
        echo -e "Usage: $0 word [-n No_of_definitions]\n"
        exit -1
fi

if [[ "$2" = "-n" ]]
then
        limit=$3
        let limit++
fi
word=$1
lynx -dump http://www.google.co.in/search?q=define:$word | \
        awk '/Defini/./Find defini/' | head -n -1 | sed 's:*:\n*:; s:^[ ]*::' | \
grep -v "[[0-9]]" | \
awk '{
if ( substr($0,1,1) == "*")
        {sub("*",++count".")}
print
}' > /tmp/$$.txt
echo
if [ $limit -ge 1 ];
then
        cat /tmp/$$.txt | sed -n "/^1\./, /$(limit)/p" | head -n -1
else
        cat /tmp/$$.txt
fi

