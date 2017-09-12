from __future__ import division
if __name__ == '__main__':
    # print in python 2 is not a function, so there are no brackets
    print "Hello, World!"

    # reading raw input and echo to screen
    my_number = int(raw_input("Pls input the number:"))
    print "My number is ", my_number

    # if-else
    if my_number % 2 != 0:
        print "this number is odd"
    else:
        print "this number is even"

    n = my_number
    # loops
    if (n >= 1) and (n <= 20):
        for i in range(0,n):
            print i*i
        
    # variable
    # 1. integer
    myint = 7
    print "myint = {:>3d}".format(myint)

    # 2. floating point
    myfloat = 7.0
    print myfloat
    myfloat2 = float(8)
    print myfloat2