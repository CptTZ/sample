#!/bin/bash
aa(){
cmd_output=$(ls|cat -n)
echo $cmd_output

aa_output=`ls|cat -n`
echo $aa_output
}


#pwd
#(cd /bin; ls)
#pwd

out=$(cat text.txt)
echo $out

out="`cat text.txt`"
echo $out

