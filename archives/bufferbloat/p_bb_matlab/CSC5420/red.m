function p = red(u)
  min = 150;
  max = 200;
  maxp = .1;
  x = u(1);
  q = u(2);
  if (q > 7999)
    p = 1;
  elseif (x < min)
    p = 0;
  elseif (x > 2*max)
    p = 1;
  elseif (x > max)
    p= (x - max)/(max)*(1-maxp)+maxp;
  else
    p= (x - min)/(max-min)*maxp;
  end;
end
