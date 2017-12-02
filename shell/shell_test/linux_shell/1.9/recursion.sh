#!/bin/bash
F()
{
	echo $1; 
	sleep 1;	
	F hello; 
}
F
