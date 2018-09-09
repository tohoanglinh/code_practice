p = polyfit(drop_prob_burst, queue_length_burst, 3);
approx_drop = polyval(p, queue_length_burst);
plot(queue_length_burst, approx_drop, 'r');
hold on;
plot(queue_length_burst, drop_prob_burst);
hold off;