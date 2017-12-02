#!/bin/bash
INPUT="ahebhahaha"
#OUTPUT=`echo $INPUT | sed 's/[^\n]/&\n/g' | sed '/^$/d' | sort | uniq -c| tr -d ' \n'`
OUTPUT=`echo $INPUT | sed 's/[^.]/&\n/g' `
echo $OUTPUT
