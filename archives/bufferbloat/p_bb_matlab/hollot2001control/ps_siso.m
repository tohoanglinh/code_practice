% Paper 1: Hollot et al., A Control Theoretic Analysis of RED
% + The figure (Close loop) is replicated from Figure 3, page 325
% + Paper 2: Ryu et al. Advances in AQM based TCP Congestion Control
clear;
clc;
% Example in page 1514, Remarks 3:
C = 3750; % packets/sec
N = 60; % no of TCP flows
R = 0.25; % secs

a_num = C*C/(2*N);
b_den = 2*N/(R*R*C);
c_den = 1/R;
num = [0 a_num];
den = [1 b_den+c_den b_den*c_den];
Ps_ol = tf(num,den)
Ps_cl = feedback(Ps_ol,1)
t = 0:0.001:2;
figure();
step(Ps_ol,t)
title('Open loop - Step response')
figure();
step(Ps_cl,t)
title('Close loop - Step response, feedback controller C(s) = 1')
%bode(Ps)
%figure();
%nyquist(Ps)
grid