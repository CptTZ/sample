#!/bin/bash
#文件名：generate_album.sh
#用途：用当前目录下的图片常见相册
echo "Creating album.."
mkdir -p thumbs
cat <<EOF > index.html
<html>
<head>
<style>
body
{
    width: 470px;
    margin: auto;
    border: lpx dashed grey;
    padding: 10px;
}
img
{
    margin: 5px;
    border: 1px solid black;
}
</style>
</head>
<body>
<center><h1> #Album title </h1></center>
<p>
EOF

for img in `ls *.img`;
do
        convert "$img" -resize "100x" "thumbs/$img"
        echo "<a href=\"$img\"><img src=\"thumbs/$img\" title=\"$img\" /></a>" >> index.html
done

cat << EOF >> index.html
</p>
</body>
</html>
EOF
echo Album generated to index.html
