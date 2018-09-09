function xdot = vdpol( t,x)

global C a A B offset

xdot = zeros(42,1);
xdot(1) = x(1)*A + x(2)*B;

% DE for instantaneous queue length
K = 0;
for i = 1:40
    K = K + x(offset+i)./(a(offset+i) + x(2)./C);
end

xdot(2) = -1.0*C + K;

% DE for individual flows
offset = 2;
for i = 1:40
    xdot(i+offset) = 1.0/(a(i+offset)+x(2)./C) - drop_p(x(1)).*x(i+offset).*x(i+offset)./(2.0*(a(i+offset)+x(2)./C));
end

% Adjustment
if (x(1) + xdot(1) < 0.0)
    xdot(1) = -1.0*x(1);
end

if (x(2)+xdot(2) < 0.0)
      xdot(2) = -1.0*x(2);
end

for i=1:40
if (x(i+offset)+xdot(i+offset) < 0.0)
      xdot(i+offset) = -1.0*x(i+offset);
end

end

