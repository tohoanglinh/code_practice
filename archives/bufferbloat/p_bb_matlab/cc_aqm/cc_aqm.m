% CPC AQM Cascade Predict Control (Window Size + Queue Length)
% Hoang-Linh TO, Inje University, 2014-12-04

clear all; close all; clc;

% Operating point (from Hollot et al.)
N = 60; % # of TCP flows
C_l = 3750;  % link capacity (packets/sec)
R0 = 0.246; % RTT (sec)

% Input system transfer function
A = (R0*C_l^2)/(2*N^2);
B = (2*N)/(R0^2*C_l);
C = N/R0;
D = 1/R0;
s = tf('s');

% Hollot et al, RED Theoretic Analysis
sys_hollot = tf(A,[1,B])*tf(C,[1,D]);
[red_i_hollot, info] = pidtune(sys_hollot,'i');
cl_sys_hollot = feedback(sys_hollot*red_i_hollot, 1)

% Linh et al. CPC
% Inner loop
in_obj= tf(A,[1,B]);
[in_C_i, info_in] = pidtune(in_obj, 'i');
cl_in_obj = feedback(in_C_i*in_obj, 1);

% Inner loop theory calculation
k_I = A/B;
T = 1/B;
T_Cwin = 2*k_I*T;
k_ii_theory = 1/T_Cwin;
Cwin_theory = k_ii_theory/s;

% Outer loop
out_obj = tf(C,[1,D])*cl_in_obj;
out_obj_zpk = zpk(out_obj);
[out_C_pid, info_out] = pidtune(out_obj, 'pid');
cl_out_obj = feedback(out_C_pid*out_obj, 1)

% Outer loop theory calculation
k_O = C/D;
T_3o = 1/D;
k_po_theory = T_Cwin/(k_I*2*k_O*T_3o);
k_io_theory = (k_po_theory*k_I)/T_Cwin;
k_do_theory = k_po_theory*T;
Cqueue_theory = k_po_theory + k_io_theory/s + k_do_theory*s;
cl_out_obj_theory = feedback(Cqueue_theory*out_obj,1)

% Plot
% opt = stepDataOptions('InputOffset', 0, 'StepAmplitude', 20);
% figure();
% stepplot(cl_out_obj_theory, 'k',...
%     cl_out_obj, 'k--',...
%     cl_sys_hollot, 'r-x',opt);
% h=findobj(gcf,'type','line');
% set(h,'linewidth',2.5);
% xlabel('Time');
% ylabel('Queue length (packets)');
% legend('CC-AQM:Simulation','CC-AQM:Theory','RED','Location','best');
% annote_x=[0.35 0.19];
% annote_y=[0.85 0.77];
% annotation('textarrow',annote_x,annote_y,'String','CC-AQM Fast Transient')
% set(findall(gcf,'-property','FontSize'),'FontSize',18)
% set(findall(gca,'-property','XColor'),'XColor','k')
% set(findall(gca,'-property','YColor'),'YColor','k')

figure();
subplot(1,2,1)
bdopts=bodeoptions;
bdopts.TickLabel.Color = [0,0,0];
bode(cl_out_obj_theory, 'k',...
    cl_out_obj, 'k--',...
    cl_sys_hollot, 'r-x',bdopts)
h=findobj(gcf,'type','line');
set(h,'linewidth',2.5);
set(findall(gcf,'-property','FontSize'),'FontSize',16)
h1_leg=legend('CC-AQM:Simulation','CC-AQM:Theory','RED','Location','south');

%figure();
subplot(1,2,2)
pzopts=pzoptions;
pzopts.TickLabel.Color = [0,0,0];
pzplot(cl_out_obj_theory, 'b',...
    cl_out_obj, 'k',...
    cl_sys_hollot, 'rx',pzopts)
set(findall(gcf,'-property','FontSize'),'FontSize',16)
h2_leg=legend('CC-AQM:Simulation','CC-AQM:Theory','RED','Location','south');
set(h1_leg, 'FontSize',12)
set(h2_leg, 'FontSize',12)
annote_x=[0.77 0.8];
annote_y=[0.75 0.82];
annotation('textarrow',annote_x,annote_y,'String','CC-AQM:Simulation-Pole','Color','b','FontSize',13)
annote_x=[0.71 0.71];
annote_y=[0.35 0.48];
annotation('textarrow',annote_x,annote_y,'String','CC-AQM:Theory-Pole','Color','k','FontSize',13)
annote_x=[0.65 0.685];
annote_y=[0.63 0.51];
annotation('textarrow',annote_x,annote_y,'String','RED-Pole','Color','r','FontSize',13)