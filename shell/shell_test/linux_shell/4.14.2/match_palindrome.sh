#!/bin/bash
if [ $# != 2 ]; then
        echo "Usage:$0 filename lenght"
fi

pre='\(.\)'

n=`expr ${2} % 2`
y=`expr ${2} / 2`
if [ "$n" == "1" ];then
        pattern="."
else
        pattern=""
fi

for ((i=0;i<y;i++))
do
     exp=`expr $2 - $i - $n - $y`
     pattern=${pre}${pattern}'\'${exp}
     echo $exp
     echo $pattern
done
    pattern='/^'$pattern'$/p'
    echo ***************************
    echo $pattern

sed -n "${pattern}" $1
