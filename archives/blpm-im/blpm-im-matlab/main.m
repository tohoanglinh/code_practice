% =========================================================
clear;
inputpara; % Input parameter at first time.
% =========================================================
% Packet Loss Probability due to balking and reneging term
% P_L = p_k + sum/lambda;
% 1, p_k = f(k)?
% 2, lambda = rho*mu
% 3, sum = g(k, c_s+j, p_s+j)
%rho = 5:0.1:30;
%rho = 0:0.1:4;
%rho = 0:0.1:5;
%rho = 0:10:100;
rho = 0:0.1:1;
% =========================================================
% Case 1: shared buffer
k1 = s + d;
s1 = s;
rho1 = rho;
plot(rho,func_pl(tau,mu,s1,d,rho1,k1),'-'); % add multiplication 3 for (17)
grid on;
hold on

%plot(x0,y0)
%plot(x16,y16)

% plot(x17_2,y17_1);
% hold on
% plot(x17_2,y17_2);
% hold on
% plot(x17_2,y17_3);
%hold on
%plot(xreduce17_2,yaverage);
%plot(x16,y16)
hold off

%plot(rho1,(func_pl(tau,mu,s1,d,rho1,k1)-0.01+0.02*rand(1)),'p','MarkerFaceColor','k')
%hold off

% Case 2
%k2 = 1 + d/s;
%s2 = 1;
%rho2 = rho/s;
%plot(rho,func_pl(tau,mu,s2,d,rho2,k2),'--');
%hold on

%plot(rho,(func_pl(tau,mu,s2,d,rho2,k2)-0.01+0.02*rand(1)),'d','MarkerFaceColor','k')
%hold off

%grid on
% =========================================================