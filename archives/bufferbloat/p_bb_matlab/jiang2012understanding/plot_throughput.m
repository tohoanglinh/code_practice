Mu = 1;
K = 0:5:80;
Lambda_eff = 0.95;
T1 = throughput(K,Lambda_eff,Mu);

plot(K,T1);
hold on

Lambda_eff = 0.99;
T2 = throughput(K,Lambda_eff,Mu);

plot(K,T2);
hold off