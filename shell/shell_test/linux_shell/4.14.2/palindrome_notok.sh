#!/bin/bash
echo $1 | sed ':loop ; s/^\(.\)\(.*\)\1/\2/; t loop; /^.\?$/{ s/.*/PALINDROME/ ; q;}; s/.*/NOT PALINDROME/ '
