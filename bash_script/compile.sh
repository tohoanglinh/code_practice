#!/bin/bash
# Author : Linh To
# Content: compile and build by gcc

echo ===================
echo C/C++ Compiling GCC
if [ -e "$1" ]; then
    echo "File $1 exists. Now cleaning..."
    rm $1
else
    echo "File $1 does not exist"
fi
gcc $1.c -o $1
echo ===================
echo Running output
echo -------------------
./$1
echo -------------------
echo DONE
echo ===================
