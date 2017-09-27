function [ psj ] = func_psj( tau,mu,s,d,rho,k,j )
%FUNC_PSJ Summary of this function goes here
%   Detailed explanation goes here

psj_a = (rho.^s)/func_factorial(s);

psj_b = func_interme(tau,mu,s,d,rho,j);

psj_c = func_p0(tau,mu,s,d,rho,k);

psj = psj_a.*psj_b.*psj_c;

end