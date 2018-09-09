clear;
clc;
load matlab.mat

plot(time,avgql_ours,'k','LineWidth',2)
hold on
plot(time,avgql_red,'k:','LineWidth',2)
hold on
plot(time,avgql_rem,'k--','LineWidth',2)
hold on
plot(time,avgql_pi,'k-.','LineWidth',2)
hold off

%title('TCP Reno: Each host (total 3) sends 200MB data (FTP Traffic)')
xlabel('Time (sec)','FontSize',14)
ylabel('Average queue length (packets)','FontSize',14)
set(gca, 'XLim',[0 60])
set(gca,'XTick',(0:10:60))
set(gca, 'fontsize',14)
h_legend=legend('OCQ','RED','REM', 'PI','Location','Best');
set(h_legend,'FontSize',14);