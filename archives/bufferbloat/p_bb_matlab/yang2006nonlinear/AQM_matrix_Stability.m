% This program determines the stability of AQM networks with single bottleneck.[1-3]. . 
% The detailed algorithm is provided in Ref. [1].
% Copyright (C) Yang XIAO, Beijing Jiaotong Univ., Oct. 26, 2007
% 
% Contact Add: Prof. Yang XIAO
% Institute of Information Science
% Beijing Jiaotong University
% Beijing 100044, China
%  E-Mail: yxiao@bjtu.edu.cn.
% 
% Recent research reveals that the fluid-based model can describe the dynamic behavior 
%for bottleneck networks [1-3].  The stability of the fluid-based model can reflect 
%whether there exists a congestion of the network. 
% 
% We develop a linearization processing [1] for fluid-based model [2,3] at equilibrium 
% points for the stability analysis of the networks with Active Queue Management (AQM).  
% 
% The bottleneck networks are described by uncertain linear time-delay systems [1], 
% then 2-D (two-dimensional) Laplace-z transform has been applied in the stability test of the network [1]. Simulations [1] verify the stability analysis for AQM network to be valid, the AQM network approaches to full utilization, while the buffer size on the order of bandwidth-delay product is necessary for the stability of the fluid model with full utilization. 
% 
% Ref: 
% [1] Y. Xiao, H. 每F. Du, Z. 每Z. Cao, and M. 每H. Lee, ※2-D stability analysis for bottleneck networks with active queue management (AQM)§, Chinese Journal of Electronics, v 16, n 3, July, 2007, p 519-523
% [2] Y. Xiao and M. 每H. Lee,§Nonlinear control of active queue management for multiple bottleneck network§, IEICE Transactions on Communications, v E89-B, n 11, November, 2006, p 3108-3113
% [3] Y. Xiao, H. 每F. Du, Z. 每Z. Cao and M. 每H. Lee, ※Active queue management for differentiated network§, IET Conference Publications, n 525, IET International Conference on Wireless Mobile and Multimedia Networks Proceedings, ICWMMN 2006, 2006, p 95.

clear; % Clear all variables' data
M=1000; % Assign 1000 to var M (sum of 1000 routers)
I=eye(2); % Assign eye matrix (diagnose with 1) to var I, dimensioin 2
h1=1e-3;  % Sample Period (10^(-3) = 0.001, take sample at each 0.001sec)
C=3000;   % Link Capacity (3000 bits/sec)
Tp=h1;    % Network Delay, assign to the same with sample period
N0=60;    % the number of TCP senders.
p0=0.1;    % Desired Dropping Probability

% Equilibrium points
W0=sqrt(2/p0);  % TCP window at equilibrium
R0=N0*W0/C;     % RTT at equilibrium
q0=C*(R0-Tp);   % Queue Length at equilibrium
qmax=q0+100;    % Maximum Queue Length
qmin=q0-100;    % Minimum Queue Length
%qmax=300
%qmin=60

NX=64;
NY=NX;

j=sqrt(-1);     % Constant (imagine)
W=2*pi/NX/h1;   % Frequency

for ii=1:20*NX
 %N0=60*(1-.2*rand(1));         % The number of TCP users to be varying
 % C=3000*(1-.2*rand(1));         % Link capacity to be varying
 %R0=q0/C;
 %q0=C*(R0-Tp);
 % R0=Tp*(1+rand(1));
W1(ii)=W*(ii-1);
f1(ii)=W1(ii)/2/pi;
%----------------
% System Matrix
A=[-N0/R0^2/C  -1/R0^2/C;   
   N0/R0 -1/R0];
%B=[-N0/R0^2/C 1/R0^2/C; 0  0];

B=[-N0/R0^2/C  2*(C*R0-q0+qmin)/(C*(qmax-qmin)*R0^2); 0  0]; % Delay Part

b0=max(real(eig(A+B*exp(-j*W1(ii)*R0))));    % Eigenvalue of System Matrix
if b0>0
e=b0;   % If e>0, the AQM network is unstable.
end
x(ii)=b0;
end
%subplot(2,1,1)
figure(1)
plot(f1,x)
ylabel('real part of Eigenvalue of system matrix');
% If x>0, the AQM network is unstable [1].
xlabel('frequency(Hz)')