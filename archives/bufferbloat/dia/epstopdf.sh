#!/bin/sh
#convert all eps to pdf files

echo "Starting to convert..."

find . -name "*.eps" -exec epstopdf {} \;

echo "Finished !"
