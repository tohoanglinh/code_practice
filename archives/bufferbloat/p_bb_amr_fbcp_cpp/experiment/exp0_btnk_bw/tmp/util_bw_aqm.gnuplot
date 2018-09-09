set terminal postscript eps enhanced color font 'Helvetica,25'
    set output "fig_util_bw_aqm.eps"
    #set title "Link Utilization with BW Changes"
    set xrange [1:]
    set yrange [0.2:105]
    set xlabel "Link Bandwidth (Mbps)"
    set logscale x
    set ylabel "Link Utilization (%)"
    set border linewidth 2
    set key right bottom
    set grid 
plot './result_bw.DropTail' using 3:12 title 'DropTail' with lp lc rgb 'black','./result_bw.RED0' using 3:12 title 'RED' with lp lc rgb 'red','./result_bw.RED5' using 3:12 title 'FBSM-AQM-CP' with lp lc rgb 'blue' lw 1.5,'./result_bw.PI' using 3:12 title 'PI' with lp lc rgb 'black','./result_bw.CoDel' using 3:12 title 'CoDel' with lp lc rgb 'black'
