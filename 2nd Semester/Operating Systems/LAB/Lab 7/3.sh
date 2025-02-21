#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Please provide at least one argument"
    exit 1
fi

S=$1
shift

for f in $@; do
    if [ -f $f ]; then
        if grep -E -q "$S" $f; then
            echo "file $f contains $S"
        else
            echo "file $f DOES NOT contain $S"
        fi
    elif [ -d $f ]; then
        if [ 0 -lt $(find $f -type f -name $S | wc -l) ]; then
            echo "dir $f contains file $S"
        fi
    fi
done
