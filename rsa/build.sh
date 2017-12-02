#!/bin/bash

gcc -o rsa bignum.c rsa.c base64.c test.c read.c -m32
