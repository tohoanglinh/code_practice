function drop = drop_p( a )

minth = 150;
maxth = 200;
pmax = 0.1;

if (a >=0.0) && (a < minth)
    drop = 0.0;
elseif (a >= minth) && (a <= maxth)
    drop = ((a-minth)/(maxth-minth))*pmax;
else
    drop = 1.0;
end

end

