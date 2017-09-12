% Prof. Jeonghoon Mo lecture, ICE0662: Network Optimization (Fall 2005)
% Lecture 7+8: Flow Control I+II

clear;
clc;

num_flows = 3;
num_links = 2;

end_sim = 500;
stepsize = 0.1;

A = [1 1 0;1 0 1];

x = zeros(num_flows, 1);
p = 10* ones(num_links, 1);
c = ones(num_links,1);

x_hist = zeros(end_sim, num_flows);
p_hist = 10*zeros(end_sim, num_links);

for i=1:end_sim
	p = p + stepsize * (A*x - c); % Link Price Algorithm
	p = max(p,0);
	
	x = 1./(A'*p); % Source Algorithm
	
	x_hist(i,:) = x'; % Update row i (x1, x2, x3) by transpose x value from algorithm.
	p_hist(i,:) = p';
end

figure(1)
clf(1) % clear current figure
plot(x_hist);
legend('x1','x2','x3');
title('Source Rate');
figure(2)
clf(2)
plot(p_hist);
legend('p1','p2');
title('Link Price');
print -deps price.eps
