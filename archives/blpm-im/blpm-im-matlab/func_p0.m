function [ p0 ] = func_p0( tau,mu,s,d,rho,k )
%FUNC_P0 Summary of this function goes here
%   Detailed explanation goes here

a1 = 0;
for j=0:s
    a1 = a1 + (rho.^j)/func_factorial(j);
end

a21 = (rho.^s)/func_factorial(s);

a22 = 0;
for j=1:(k-s)
    a22 = a22 + func_interme(tau,mu,s,d,rho,j);
end

p0 = 1./(a1 + a21.*a22);

end