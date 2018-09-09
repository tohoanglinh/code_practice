clear;
clc;
load matlab.mat

bar(throughput,0.25,'k')
set(gca,'XTickLabel', str,'XTick',1:numel(str))
ylabel('Throughput(Mbps)','FontSize',14)
set(gca, 'fontsize',14)