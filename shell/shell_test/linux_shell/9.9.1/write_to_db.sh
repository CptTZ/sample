#!/bin/bash
USER="root"
PASS="asdf"

if [ $# -ne 1 ];
then
        echo $0 DATAFILE
        echo
        exit 2
fi

data=$1
while read line;
do
        oldIFS=$IFS
        IFS=,
        values=($line)
        values[1]="\"`echo ${values[1]} | tr ' ' '#'`\""
        values[3]="\"`echo ${values[3]}`\""
        query=`echo ${values[@]} | tr ' #' ', ' `
        IFS=$oldIFS

        mysql -u $USER -p$PASS students <<EOF
INSERT INTO students VALUES($query);
EOF
        
done< $data
echo worte data into DB
