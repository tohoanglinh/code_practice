function [ out_etedelay ] = etedelay( K, Lambda_eff, Mu )
% End-to-end Delay Analysis
% Processor in the bottleneck hop would be nearly fully-utilized
% Which means "Lambda_eff / Mu ==> 1"
% E[D_bottleneck] grow faster than buffer size K.

% Input parameters:
% (1) Buffer size: K
% (2) Efficient arrival rate: Lambda_eff
% (3) Service rate: Mu
% Related: Utilization ratio: Rho = Lambda_eff/Mu

% =======================================================================
A = 1./(Mu.*(1 - Lambda_eff./Mu)); % Fixed with Rho and Lambda_eff

B = (K+1)./Lambda_eff; % CHANGING

C = 1./(1-(Mu./Lambda_eff).^(K+1)); % CHANGING

out_etedelay = A + B.*C;
% =======================================================================
end

