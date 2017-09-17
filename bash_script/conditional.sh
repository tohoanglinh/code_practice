#!/bin/bash
# a sample bash script, by Linh

read inputchar
if [ "$inputchar" == "Y" ] || [ "$inputchar" == "y" ]; then
    echo "YES"
elif [ "$inputchar" == "N" ] || [ "$inputchar" == "n" ]; then
    echo "NO"
fi