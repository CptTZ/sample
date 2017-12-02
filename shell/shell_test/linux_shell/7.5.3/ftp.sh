#!/bin/bash
HOST="172.17.52.164"
USER="aaa"
PASSWD="123456"
ftp -i -n $HOST <<EOF
user $USER $PASSWD
binary
get thread
put limaoyuan.ftp
quit
EOF
