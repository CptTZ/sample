#!/bin/bash +x
#文件名:rename.sh
#用途：重命名.jpg和.png文件
count=1
for img in *.img *.png
do
	new=image-$count.${img##*.}
	echo "new:$new img:$img"
	mv "$img" "$new" 2> /dev/null
	if [ $? -eq 0 ];
	then
		echo "Renameing $img to $new"
		count=`expr $count + 1`
	fi
done
