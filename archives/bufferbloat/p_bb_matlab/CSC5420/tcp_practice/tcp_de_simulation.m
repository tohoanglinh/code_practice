% Hoang-linh TO 
% RED simulation  in Matlab

clear;
clc;

global C ts a A B alpha X offset

for C = 100:200:1300
alpha = 0.0001; % weighting factor in exponential average
ts = 1.0/C; % time step size

for i = 1:42
    a(i) = 0.2;
end

% Differential Equation for Avg Queue Size estimation in RED
A = log(1.0-alpha)/ts;
B = -1.0 * A;

X0 = zeros(42,1);
X0(1) = 0.0; % set avg queue length = 0 at time 0  
X0(2) = 0.0; % set instantaneous queue length = 0.0 at time t = 0;
offset = 2;

for i = 1:40
    X0(i+offset) = 1.0;
end

% solve the DE using ode23 over some time interval
t0 = 0;
tf = 70.0;
disp('enter ode23 function');
[t,X] = ode23('vdpol', [t0 tf], X0);
disp('get out of ode23 function');
figure;
plot(t,X)
xlabel('time');
title('W(t), X(t), Q(t)');
end

%C = 5.0*1024.0*1024.0/(500.0*8); % link capacity or service capacity (packets/sec)