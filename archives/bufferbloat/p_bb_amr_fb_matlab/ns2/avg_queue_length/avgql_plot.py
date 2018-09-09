#!/usr/bin/python

import scipy.io
import matplotlib
from pylab import *
import numpy as np
import matplotlib.ticker as plticker

data = scipy.io.loadmat('matlab.mat')

time = data['time']
avgql_ours = data['avgql_ours']
avgql_red = data['avgql_red']
avgql_rem = data['avgql_rem']
avgql_pi = data['avgql_pi']

font = {'size': 18, 'family':'serif'}
matplotlib.rc('font',**font)
matplotlib.rc('text', usetex=True)

f1=figure()
plot(time,avgql_ours,'k',label='FB-OCQ',  linewidth=2.0)
plot(time,avgql_red,'k:',label='RED',  linewidth=2.0)
plot(time,avgql_rem,'k--',label='REM',  linewidth=2.0)
plot(time,avgql_pi,'k-.',label='PI',  linewidth=2.0)
legend(loc='best', fontsize=16)
xlim([0,60])
xlabel('Time(sec)')
ylabel('Average queue length (packets)')

show()
