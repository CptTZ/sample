#!/bin/bash
var=""
(var=lookback;echo $var)
echo $var


(echo "a"; echo "b";) |awk '{print NR,$0}'
