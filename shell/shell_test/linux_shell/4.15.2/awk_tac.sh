#!/bin/bash
seq 9 | \
awk '{ aa[NR]=$0; num=NR }
END{ for(;num>-1;num--){ print aa[num]; } 
}'
