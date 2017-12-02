#!/bin/bash
sudo lsof -ni | grep ":[0-9a-zA-Z]\+->" -o | grep "[0-9a-zA-Z]\+" -o | sort | uniq
