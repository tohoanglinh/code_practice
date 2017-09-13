from __future__ import print_function
import sys
if __name__ == '__main__':
    n = int(raw_input())

    f = open('log', 'w')

    f.write('Linh')

    for i in range(1, n+1):
        # print i,
        # print(i,sep="",end="",file=sys.stdout)
        # print(i,sep="",end="",file=f)
        f.write(str(i))     # file.write() method takes a string as an argument, 
                            # so you have to use the str() function on the item
        
    f.close()
