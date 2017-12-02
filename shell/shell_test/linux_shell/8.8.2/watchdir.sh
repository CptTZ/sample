#/bin/bash
path=$1
inotifywait -m -r -e create,move,delete $path -q
