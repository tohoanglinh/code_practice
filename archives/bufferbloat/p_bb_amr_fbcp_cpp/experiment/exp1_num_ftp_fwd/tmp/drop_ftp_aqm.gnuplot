set terminal postscript eps enhanced color font 'Helvetica,25'
    set output "fig_drop_ftp_aqm.eps"
#    set title "Packet Drop Rate with FTP Flows Changes"
    set xrange [1:]
    set yrange [-1:9]
    set xlabel "Offered Load: Number of FTP Flows"
    set logscale x
    set ylabel "Packet Drop Rate (%)"
    set border linewidth 2
    set key right top
    set grid 
plot './result_ftp.DropTail' using 5:18 title 'DropTail' with lp lc rgb 'black','./result_ftp.RED0' using 5:18 title 'RED' with lp lc rgb 'red','./result_ftp.RED5' using 5:18 title 'FBSM-AQM-CP' with lp lc rgb 'blue' lw 1.5,'./result_ftp.PI' using 5:18 title 'PI' with lp lc rgb 'black','./result_ftp.CoDel' using 5:18 title 'CoDel' with lp lc rgb 'black'
