#!/bin/bash

while [ $# -ge 3 ]; do
    f=$1
    n=$2
    m=$3
    if ! echo $n | grep -E "^[0-9]+$" || ! echo $n | grep -E "^[0-9]+$"; then
        echo "n=$n or m=$m might not be numbers"
    elif [ $n -gt $m ]; then
        echo "n($n) should not be greater than m($m)"
    else
        if [ -d $f ]; then
            c=$(find $f -type f | wc -l)
            if [ $c -ge $n ] && [ $c -le $m ]; then
                echo "Directory $f has $c regular files, which is within the [$n, $m] interval"
            else
                echo "Directory $f has $c regular files, outside of the [$n, $m] interval"
            fi
        else
            echo "Provided name: $f is not a directory or doesn't exist"
        fi
    fi
    shift 3
done

if [ $# -gt 0 ]; then
    echo "Incomplete triplet"
fi