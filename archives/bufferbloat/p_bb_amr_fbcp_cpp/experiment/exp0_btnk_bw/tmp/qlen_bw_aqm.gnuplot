set terminal postscript eps enhanced color font 'Helvetica,25'
    set output "fig_qlen_bw_aqm.eps"
    #set title "Percent of Mean Queue Length with BW Changes"
    set xrange [1:]
    set yrange [-1:100]
    set xlabel "Link Bandwidth (Mbps)"
    set logscale x
    set ylabel "Mean Queue Length (%)"
    set border linewidth 2
    set key right top
    set grid 
plot './result_bw.DropTail' using 3:15 title 'DropTail' with lp lc rgb 'black','./result_bw.RED0' using 3:15 title 'RED' with lp lc rgb 'red','./result_bw.RED5' using 3:15 title 'FBSM-AQM-CP' with lp lc rgb 'blue' lw 1.5,'./result_bw.PI' using 3:15 title 'PI' with lp lc rgb 'black','./result_bw.CoDel' using 3:15 title 'CoDel' with lp lc rgb 'black'
