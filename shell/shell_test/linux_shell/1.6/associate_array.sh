#!/bin/bash
declare -A fruits
fruits=([apple]="100yuan" [orange]="200yuan")
echo "Apple costs ${fruits[apple]}"
echo ${!fruits[*]}
echo ${!fruits[@]}
