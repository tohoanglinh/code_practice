clear;
clc;
load matlab.mat

plot(tocq,ocq,'k','LineWidth',2)
hold on
plot(tred,red,'k--','LineWidth',2)
hold off

xlabel('Time (sec)','FontSize',14)
ylabel('Dropping Probability','FontSize',14)
set(gca, 'XLim',[0 60])
set(gca,'XTick',(0:10:60))
set(gca, 'fontsize',14)
h_legend=legend('OCQ','RED','Location','Best');
set(h_legend,'FontSize',14);