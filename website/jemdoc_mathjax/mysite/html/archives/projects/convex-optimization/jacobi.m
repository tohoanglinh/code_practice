% Parallel and Distributed Computing: Numerical Methods, D.P. Bertsekas and J.N. Tsitsiklis
% Section 2.4, 2.6

clear;
clc;

% a11 = -1; a12 = 2;
% a21 = 2; a22 = -1;

% Matrix A(2x2) and b(2x1)
a11 = 2; a12 = -1;
a21 = -1; a22 = 2;
b1 = 0; b2 = 0;

% We need to solve Ax = b
A = [a11 a12; a21 a22];
b = [b1;b2];

% Initialize
x(1) = 10;
y(1) = 10;
t = 1;

% Stop criterion
tolerance = 10e-3;
max_iteration = 50;

% Jacobi loop
while max_iteration > 0
   x(t+1) = -1/a11 * (a12 * y(t) - b1);
   y(t+1) = -1/a22 * (a21 * x(t) - b2);
   if abs(x(t+1) - x(t)) < tolerance
       t = t + 1;
       break;
   end
   t = t + 1;
   max_iteration = max_iteration - 1;
end

% Display results
display('System of Linear Equation: Jacobi Iterative Method')
fprintf('Number of Iterations: %4.0f \n', 50-max_iteration)
fprintf('Solution (x, y) = (%4.2f,%4.2f) \n',x(t), y(t))
