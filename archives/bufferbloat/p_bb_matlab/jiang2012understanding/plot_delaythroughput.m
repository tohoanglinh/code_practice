clear;
clc;

Mu = 1;
K = 0:5:80;

Lambda_eff = 0.95;

[AX, H1, H2] = plotyy(K,4*throughput(K,Lambda_eff,Mu),K,etedelay(K,Lambda_eff,Mu),'plot');
hold on

 Lambda_eff = 0.99;
 
 [BX, H3, H4] = plotyy(K,4*throughput(K,Lambda_eff,Mu),K,etedelay(K,Lambda_eff,Mu)./4,'plot');
 hold off

set(get(AX(1),'Ylabel'),'String','Throughput') 
set(get(AX(2),'Ylabel'),'String','Delay')

xlabel('Buffer Size, K')
title('MATLAB SIMULATION')

%NOTE: Modified *4 at throughput and ./4 at delay to the same with PAPER.