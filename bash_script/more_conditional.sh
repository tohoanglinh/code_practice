#!/bin/bash
# a sample bash script, by Linh

read x
read y
read z
if [ "$x" == "$z" ] && [ "$y" == "$z" ]; then
    echo "EQUILATERAL"
elif [ "$x" == "$z" ] || [ "$y" == "$z" ] || [ "$y" == "$x" ]; then
    echo "ISOSCELES"
else
    echo "SCALENE"
fi