% Copyright (c) 2007, Hoang-Linh TO
% SRFCS: Step Response of Feedback Control System
% Course: "Modeling and Simulation"
% Department of Industrial Automation
% Hanoi University of Science and Technology

k1=50;
k2=0.5;
t1=0.02;t2=0.03;
num=[k1];
den=[t1*t2,t1+t2,1,k1*k2];
step(num,den);
title('Dac tinh qua do cua Nhom 1');
ylabel('y(t)');xlabel('t');
