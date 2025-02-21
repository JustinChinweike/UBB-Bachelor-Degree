#!/bin/bash

# the home folder can be extracted from the /etc/passwd file

for home_folder in $(awk -F: '$1 ~ /^(ex|yz)[0-9]+$/ {print $6}' /etc/passwd); do
    user=$(awk -F: -v x=$home_folder ' $6==x {print $5}' /etc/passwd | awk -F"-" '{print $1}')
    # the -d option for ls prints the properties for the directory given as an argument, not its content
    if ! ls -ld $home_folder | grep -E -q "^.{4}-{6}"; then
        echo $user" - "$home_folder
    fi
done | sort