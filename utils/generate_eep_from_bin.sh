#!/bin/bash

if [ -z "$1" ]
then
    echo "Please specify a binary image"
    exit 1
else
    root="${BASH_SOURCE%/*}/"
    python $root/bin/trim.py $PWD/$1 && python $root/bin/bin2hex.py -r 2 --binaries 0x00,$1 -o $PWD/$1.eep
fi
