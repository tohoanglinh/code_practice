# cd gitworks/code_practice_python

#import system modules

#method to import python functions from arbitrary files or paths.
import sys
sys.path.insert(0, 'lib/')
from maths import *

def main():
    print("1 + 2 = {}, 5 + 4 = {}.".format(tinh_tong(1,2), tinh_tong(5,4)))


if __name__ == '__main__':
    main()