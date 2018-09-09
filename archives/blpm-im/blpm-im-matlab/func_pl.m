function [ pl ] = func_pl( tau, mu, s, d, rho, k )
% func_pl Packet Loss Probability due to balking and reneging term
% P_L = p_k + sum/lambda;

sum = 0;
for j=1:(k-s)
    sum = sum + func_csi(tau,mu,s,d,rho,j)*func_psj(tau,mu,s,d,rho,k,j);

end

pk = func_psj(tau,mu,s,d,rho,k,k-s);

pl = pk + sum./(rho*mu);

end