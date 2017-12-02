#!/bin/bash
num=0
for i in `echo $1/*`
do
    new_pic=${i%/*}pic${num}.${i##*.}
    mv $i $new_pic
    let num=num+1
done
