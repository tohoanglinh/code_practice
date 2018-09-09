clear; clc;
%% System Matrices
% dot(x) = Ax + Bu
% y = Cx
N = 100; % number of TCP sessions
R = 0.2; % sec
Cl = 1250; % packets/sec
qd = 150; % packets
w0 = 2.5; % packets
p0 = 2/w0^2;

A = [ -N/(R^2*Cl) 0
    N/R -1/R];

Ad = [ -N/(R^2*Cl) 1/(R^2*Cl)
    0 0];

B = [-R*Cl^2/(2*N^2)
    0];

C = [0 1];

%% Open-loop stability or not?
% One of the first things we want to do is analyze whether the open-loop system (without any control) is stable. 
% As discussed in the Introduction: System Analysis section, the eigenvalues of the system matrix, A, 
% (equivalent to the poles of the transfer fucntion) determine the stability. The eigenvalues of the A matrix are the values of s where det(sI - A) = 0.
poles = eig(A);
% if one of poles is in the right-half plane (i.e. has positive real part)
% --> system is unstable in open-loop (without control)
% if all poles are in the left-half plane --> system is stable
t = 0:0.01:10;
u = zeros(size(t));
x0 = [0.1 0];
sys = ss(A,B,C,0);
[y,t,x] = lsim(sys,u,t,x0);
plot(t,y)
title('Open-loop response to non-zero initial condition')
xlabel('Time(sec)')
ylabel('Queue Length (packets)')