#/bin/bash
start=$(date +%s)
sleep 5;
end=$(date +%s)
difference=$(( end - start ))
echo Time taken to execute commands is $difference seconds.
