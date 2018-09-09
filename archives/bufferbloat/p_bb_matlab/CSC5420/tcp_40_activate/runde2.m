% define the initial conditions for the DE
clear;
clc;

global C alpha ts A B a offset X

C = 5.0*1024.0*1024.0/(500.0*8);  % in unit of packet per second
alpha = 0.0001;         % weighting  factor in exponential average
ts = 1.0/C;             % time step size
for i=1:42
    a(i) = 0.2;
end

% D.E. for average queue size estimate
A = log((1.0-alpha))/ts;
B = -1.0*A;

X0 = zeros(42,1);
X0(1) = 0.0;    % set average queue length = 0 at time t=0
X0(2) = 0.0;    % set instantenous queue length = 0.0 at time t=0
offset=2;
for i=1:40
   X0(i+offset) = 1.0;
end

% solve the DE using ode23 over some time interval
t0=0;
tf=70.0;
disp('enter ode23 function')
[t,X] = ode23('vdpol2', [t0 tf], X0);
disp('get out of ode23 function')
plot(t,X)
xlabel ('time')
title ('W(t), x(t), q(t)')