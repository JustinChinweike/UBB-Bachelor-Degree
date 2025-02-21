#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Please provide at least one argument"
    exit 1
fi

while true; do
    clear
    for u in $@; do
        if grep -E -q "^$u:" /etc/passwd ; then
        # alternate version: if id $u > /dev/null 2> /dev/null; then
            count=$(ps -u $u | awk 'NR > 1' | wc -l)
            echo "$u - $count"
        fi
    done
    sleep 1
done
