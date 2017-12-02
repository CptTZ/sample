#!/bin/bash

egrep -o '[0-9a-zA-Z.]+@[0-9a-zA-Z]+\.[a-zA-Z]{2,4}' $1
