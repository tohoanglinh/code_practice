function [ interme ] = func_interme( tau,mu,s,d,rho,j )
%FUNC_INTERME Summary of this function goes here
%   Detailed explanation goes here

tuso = (rho*mu).^j;

mauso = 1;
for i=0:(j-1)
    mauso = mauso*(s*mu+func_csi(tau,mu,s,d,rho,j-i));
end

interme = tuso/mauso;

end