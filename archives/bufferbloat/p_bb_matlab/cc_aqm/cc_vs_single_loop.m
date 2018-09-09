clear;
clc;
P2 = zpk([],-2,3);
P1 = zpk([],[-1 -1 -1],10);
% The plant model is P = P1*P2
P = P1*P2;
% Use a PID or PIDSTD object to define the desired controller structure
C = pidstd(1,1);
% Tune PI controller for target bandwidth is 0.2 rad/s
C = pidtune(P,C,0.2);

C2 = pidtune(P2, pidstd(1,1),2);
% Inner loop system when the control loop is closed first
clsys = feedback(P2*C2,1);
% Plant seen by the outer loop controller C1 is clsys*P1
C1 = pidtune(clsys*P1,pidstd(1,1),0.2);

% single loop system for reference tracking
sys1 = feedback(P*C,1);
set(sys1,'Name','Single Loop');
% cascade system for reference tracking
sys2 = feedback(clsys*P1*C1,1);
set(sys2,'Name','Cascade');
% plot step response
figure;step(sys1,'r',sys2,'b')
legend('show','location','southeast')
title('Reference Tracking')

% single loop system for rejecting d2
sysd1 = feedback(P1,P2*C);
set(sysd1,'Name','Single Loop');
% cascade system for rejecting d2
sysd2 = P1/(1+P2*C2+P2*P1*C1*C2);
set(sysd2,'Name','Cascade');
% plot step response
figure;step(sysd1,'r',sysd2,'b')
legend('show')
title('Disturbance Rejection')