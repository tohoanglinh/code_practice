function [ EN ] = func_average_no( tau, mu, s, d, rho, k )
%FUNC_AVERAGE_NO Summary of this function goes here
%   Detailed explanation goes here
% ==================================================================
N1 = 0;
for j=1:(k-s)
    A = func_interme(tau,mu,s,d,rho,j);
    N1 = N1 + (s+j).*A;
end
% ==================================================================
p0 = func_p0(tau,mu,s,d,rho,k);
N2 = 0;
for j=1:s
    N2 = N2 + (p0.*(rho.^j))/func_factorial(j-1);
end
% ==================================================================
EN = N2 + N1.*(rho.^s)/func_factorial(s);

end