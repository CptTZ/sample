#!/bin/bash
egrep -o "http://[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,4}" $1
