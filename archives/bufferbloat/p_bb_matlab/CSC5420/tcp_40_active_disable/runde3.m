% define the initial conditions for the DE
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
tf=75.0;
[t,X] = ode23('vdpol3', [t0 tf], X0);
%plot(t,X)
% get the dimension of X
[row1,col1] = size(t);
X0(1) = X(row1,1);
X0(2) = X(row1,2);
% let the first 20 flows go down
for i=1:40
   X0(i+offset) = 0.0;
end
for i=21:40
   X0(i+offset) = X(row1,i+offset);
end
t0=75.0;
tf=300.0;
[t1,X1] = ode23('vdpol3',[t0 tf], X0);

% get the dimension of X1
[row1,col1] = size(t1);
X0(1) = X1(row1,1);
X0(2) = X1(row1,2);
% let the first 20 flows come back up 
for i=1:20
   X0(i+offset) = 1.0; 
end
for i=21:40
   X0(i+offset) = X1(row1,i+offset);
end
t0=300.0;
tf=380.0;
[t2,X2] = ode23('vdpol3',[t0 tf], X0);

ft=[t;t1;t2];
fX=[X;X1;X2];
plot(ft, fX)
xlabel ('time')
title ('W(t), x(t), q(t)')
