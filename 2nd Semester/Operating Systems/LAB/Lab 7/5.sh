#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Must provide exactly one argument"
    exit 1
fi

if ! echo $1 | grep -E "^[0-9]+$"; then
    echo "Argument does not seem to be a number"
    exit 1
fi

total=0
files=""

while [ $total -lt $1 ]; do
    read -p "Input filename: " file
    if [ -f $file ]; then
        lines=$(wc -l $file | awk '{print $1}')
        total=$((total+lines))
        files="$files $file"
        echo "File $file has $lines lines; Total number of lines so far: $total"
    else
        echo "Not a regular file!"
    fi
done

cat $files | head -n $1
