#!/bin/bash
a=(1 2 3)
echo $a
a=("heihei" "lala" "haha")
echo $a


echo ${#a[@]}
echo ${#a[*]}

echo ${a[@]}
echo ${a[*]}
echo ${a[@]/lala/kaka}

echo ${a[0]}
echo ${a[1]}
echo ${a[2]}


a[2]="nimei"
echo ${a[2]}
a[2]=nimei
echo ${a[2]}

echo ${a[*]:1:2}
echo ${a[*]:0:1}

unset a[1]
echo ${a[*]}
