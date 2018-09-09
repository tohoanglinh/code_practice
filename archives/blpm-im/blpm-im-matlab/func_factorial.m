function [ fact_n ] = func_factorial( n )
%FUNC_FACTORIAL Summary of this function goes here
%   Detailed explanation goes here

fact_n = 1;
for i=1:n
    fact_n = fact_n*i;
end

end