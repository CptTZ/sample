#!/bin/bash
echo $1 | tr ' ' '\n' | tac | tr '\n' ' ' | rev
