% Hollot et al. "A control theoretic of RED", INFOCOM

clear;
clc;

% Operating point
N = 60; % # of TCP flows
C_l = 3750;  % link capacity (packets/sec)
R0 = 0.246; % RTT (sec)


% Input system transfer function
A = (R0*C_l^2)/(2*N^2);
B = (2*N)/(R0^2*C_l);
C = N/R0;
D = 1/R0;

% Test
sys = tf(A,[1,B])*tf(C,[1,D])
cl_sys = feedback(sys,1,-1)
% Plot
subplot(2,1,1)
step(sys)
legend('Single-Loop (Open)')
subplot(2,1,2)
step(cl_sys)
legend('Single-Loop (Close)')

% Test
sys_hollot = tf(A,[1,B])*tf(C,[1,D])
[red_i_hollot, info] = pidtune(sys_hollot,'i')
cl_sys_hollot = feedback(sys_hollot*red_i_hollot, 1)
% Plot
opt = stepDataOptions('InputOffset', -1, 'StepAmplitude', 20)
step(cl_sys_hollot,opt)
