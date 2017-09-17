# gnuplot -c plot.gp pdf 'test.pdf' 'data.dat'

set terminal ARG1
set output ARG2
plot ARG3 title ARG3 with linespoints
unset output