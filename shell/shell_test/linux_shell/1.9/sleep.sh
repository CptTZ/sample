#!/bin/bash
echo -n Count:
tput sc

count=0;
while true
do
	if [ $count -lt 40 ]; then
		set -x
		let count++;
		sleep 1;
		tput rc
		tput ed
		echo -n $count;
		set +x
	else
		exit 0;
	fi
done
