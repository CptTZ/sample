#!/bin/bash
your_name='cainiao'
str="Hello, I know you are \"$your_name\"!"
echo $str

#strcat
greeting="hello, "$your_name"!"
greeting_1="hello, ${your_name} !"
greeting_2="hello"" haha"
echo $greeting $greeting_1 $greeting_2
echo ""
#strlen
echo ${#greeting}
#strcut
echo ${str:0:5}

echo $str

echo `expr index "$str" you`
