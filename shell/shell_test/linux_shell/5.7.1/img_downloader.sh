#!/bin/bash
#图片下载器
#文件名：img_downloader.sh
if [[ $# != 3 ]]; then
   echo "Usage:$0 URL -d DIR"
   exit -1
fi

for i in {1..4}
do
    case $1 in
        -d)
            shift; dir=$1; shift;;
        *)
            url=${url:-$1}; shift;;
    esac
done

mkdir -p $dir
base_url=$(echo $url | egrep -o "https?://[a-z.]+")

curl -s $base_url | egrep -o "<img src=[^>]*>" |
sed "s/<img src=\([^>]*\).*/\1/g" | tee /tmp/$$.list

sed -i "s|^//||" /tmp/$$.list
cat /tmp/$$.list

cd $dir;

while read filename
do
        echo $filename
    curl -s -O $filename --silent
done < /tmp/$$.list

