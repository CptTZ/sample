#!/bin/bash
awk '{ aa[NR % 10]=$0 } END{for(i=1;i<11;i++){print aa[i % 10];}}' $1
#awk '{ aa[NR % 10]=$0 } END{for(i=1;i<11;i++){print $i;}}' $1
