#!/usr/bin/python

from __future__ import print_function
import fileinput
import re

fn = "input.txt" #your file name

for line in fileinput.input(fn, inplace=1):
    match = re.search("//(.)", line)
    if match:
        print(match.group(0).replace("//",""))
    else:
        print(line, end="")
