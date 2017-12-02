#!/bin/bash
file_jpg="sample.jpg"
name=${file_jpg%.*}
echo File name is: $name
extension=${file_jpg#*.}
echo File name is: $extension
url="www.google.cn"
last=${url#*.}
echo "use # get last:$last"
last=${url##*.}
echo "use ## get last:$last"
pre=${url%.*}
echo "use % get pre:$pre"
pre=${url%%.*}
echo "use %% get pre:$pre"
