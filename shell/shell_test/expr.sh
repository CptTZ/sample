#!/bin/bash
str="hello everyone, my name is limaoyuan"
echo 'use ${#val} get'
echo ${#str}

echo `expr length "$str"`

echo `expr index "$str" "limaoyuan"`

echo `expr match "$str" hell.*`

echo `expr match "$str" hell`

echo `expr match "$str" haha`

echo `expr substr "$str" 10 11`

teststr="200911111111 readnow please"
echo ${teststr#2*1}

echo ${teststr##2*1}

lala="you are not a good boy, you you you"
echo ${lala/you/sha}
echo ${lala//you/sha}
