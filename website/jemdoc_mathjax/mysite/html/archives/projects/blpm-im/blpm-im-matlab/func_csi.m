function [ csi ] = func_csi( tau,mu,s,d,rho,i )
%FUNC_CSI Summary of this function goes here
%   Detailed explanation goes here

tuso = tau^(i-1)*exp(-s*mu*tau); % scalar

syms t;
mauso = eval(int(t^(i-1)*exp(-s*mu*t),0,tau));

csi = tuso/mauso;

end