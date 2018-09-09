#!/usr/bin/python

import scipy.io
import matplotlib
from pylab import *
import numpy as np
import matplotlib.ticker as plticker

#data = scipy.io.loadmat('matlab.mat')

#throughput = data['throughput']
y = [ 0.075904  ,  0.08214613,  0.0661152 ,  0.06498027]
N = len(y)
x = range(N)

font = {'size': 18, 'family':'serif'}
matplotlib.rc('font',**font)
matplotlib.rc('text', usetex=True)
width = 0.20

f1=figure()
bar(x,y,width,color='k')
#ticklabel_format(style='sci', axis='y', scilimits=(0,0))
xticks([0.25,1.1,2.1,3.1],['FB-OCQ', 'RED', 'REM', 'PI'])
legend(loc='best', fontsize=16)
ylabel('Throughput(Mbps)')

show()
