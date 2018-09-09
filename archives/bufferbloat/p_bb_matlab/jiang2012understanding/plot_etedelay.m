clc;
clear;

Mu = 1;
K = 0:5:80;
Lambda_eff = 0.9;

D1 = abs(etedelay(K,Lambda_eff,Mu)./3); 

plot(K,D1);
hold on

Lambda_eff = 0.95;

D2 = abs(etedelay(K,Lambda_eff,Mu)./3);  

plot(K,D2);

hold on

Lambda_eff = 0.98;
D3 = abs(etedelay(K,Lambda_eff,Mu)./3); 
plot(K,D3);

hold off