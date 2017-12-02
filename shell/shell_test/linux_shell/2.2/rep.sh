#!/bin/bash
`echo $output | sed 's/[^\n]/&\n/g' | sed '/^$/d' | sort | uniq -c | tr -d ' \n'`
