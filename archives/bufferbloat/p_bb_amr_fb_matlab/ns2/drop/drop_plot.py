#!/usr/bin/python

import scipy.io
import matplotlib
from pylab import *
import numpy as np
import matplotlib.ticker as plticker

data = scipy.io.loadmat('matlab.mat')

tocq = data['tocq']
ocq = data['ocq']
tred = data['tred']
red = data['red']

font = {'size': 18, 'family':'serif'}
matplotlib.rc('font',**font)
matplotlib.rc('text', usetex=True)

f1=figure()
plot(tocq,ocq,'k',label='FB-OCQ',  linewidth=2.0)
plot(tred,red,'k--',label='RED',  linewidth=2.0)
legend(loc='best', fontsize=16)
xlabel('Time (sec)')
ylabel('Dropping Probability')

show()
