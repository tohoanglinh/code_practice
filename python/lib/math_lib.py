import sys
import math
import time

global LLCP_PTYPE_SYMM
global LLCP_PTYPE_CONNECT

LLCP_PTYPE_SYMM    = 0x00
LLCP_PTYPE_CONNECT = 0x04

def sum(a,b):
    global LLCP_PTYPE_SYMM
    global LLCP_PTYPE_CONNECT
    LLCP_PTYPE_SYMM = 3
    LLCP_PTYPE_CONNECT = 2
    return int(a)+int(b)

def diff(a,b):
    print(LLCP_PTYPE_SYMM + 1)
    return int(a)-int(b)