% define dropping function in RED
function drop = p(a)
% initialie control points
min=150.0;
max=200.0;
pmax=0.1;
if (a >= 0.0) & (a < min)
   drop = 0.0;
elseif (a >= min) & (a <= max)
   drop = ((a - min)/(max-min))*pmax;
else
   drop = 1.0;
end

