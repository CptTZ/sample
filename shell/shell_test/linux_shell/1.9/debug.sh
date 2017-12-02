#!/bin/bash -xv
function DEBUG()
{
	[ "$_DEBUG" == "on" ] && $@ || :
}

for i in {1..10}
do
	DEBUG echo $i
done
