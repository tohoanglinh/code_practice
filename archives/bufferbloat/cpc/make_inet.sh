#!/bin/bash
 
# Hoang-Linh TO
# Recompile inet to add new modules
 
# change this path to your inet-path
cd ~/omnetpp/omnetpp-4.2.2/samples/inet

make cleanall

make makefiles

make
