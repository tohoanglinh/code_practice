function [ out_throughput ] = throughput( K, Lambda_eff, Mu )
%THROUGHPUT Mbps

A = Lambda_eff - Mu;

B = 1 - (Lambda_eff./Mu).^(K+1);

out_throughput = Mu + A./B;

end