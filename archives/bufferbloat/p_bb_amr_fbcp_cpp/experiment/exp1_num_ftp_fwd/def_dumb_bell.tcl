#
# Copyright (c) 2007  NEC Laboratories China.
# All rights reserved.
#
# Released under the GNU General Public License version 2.
#
# Authors:
# - Gang Wang (wanggang@research.nec.com.cn)
# - Yong Xia   (xiayong@research.nec.com.cn)
#
#
# $Id: def_dumb_bell.tcl,v 1.3 2007/04/25 07:55:42 xiayong Exp $
#
# This file is for dumb_bell simulation settings.
#
#
#            Src_1                                    Sink_1 
#                 \                                  / 
#                  \           bottleneck           / 
#          Src_2 --- Router1 -------------- Router2 --- Sink_2 
#                  /                                \ 
#                 /                                  \ 
#            Src_N                                    Sink_N 
#    
#                     Fig 1. A Dumb-bell topology. 
#


# 1, topology setting
set btnk_bw 10 	                        ;# in Mbps
set rttp 80                             ;# in ms
set per 0                               ;# static link packet error rate. range 0 to 1.
set rtt_diff 0                          ;# rtt difference in ms


# 2, traffic setting
set sim_time 100		        ;# total simulation time in sec

# 2.1 ftp
set num_ftp_fwd 5			;# number of forward ftp flows
set num_ftp_rev 5			;# number of reverse ftp flows
set TCP_scheme Reno			;# the TCP scheme employed by ftp
set useAQM 2                ;# 0: not to use AQM in routers
set AQM_scheme RED			;# the AQM scheme employed by queue management in bottleneck link
set redmod 0				;# redmod

# 2.2 web
set http_rate 15	        	;# http connection generation rate

# 2.3 voice
set num_voice 5			        ;# number of voice flows

# 2.4 video
set num_streaming_fwd 5			;# number of forward streaming flows
set num_streaming_rev 5			;# number of reverse streaming flows
set streaming_rate 640Kb		;# rate of each streaming flow
set streaming_pktsize 840 		;# packet size in byte

# 3, statistics/graph setting
set html_index 100 			;# save results in index100.html. if -1 no html file
set show_bottleneck_stats 1  	        ;# show bottleneck link stats, such as utilization and queue size
set show_graph_ftp 1	                ;# show ftp throughput
set show_graph_http 1                   ;# show http statistics
set show_graph_voice 1 			;# show voice statistics
set show_graph_streaming 1  	        ;# show streaming statistics
set show_convergence_time 0 	        ;# show forward FTP convergence time
set verbose 1				;# show detail information

# that's it -- end.
set verbose  0
set show_graph_ftp 0
set show_graph_http 0
set show_graph_voice 0
set show_graph_streaming 0
set show_convergence_time 0
set useAQM 2
set TCP_scheme Reno
set AQM_scheme DropTail
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set AQM_scheme RED
set redmod 0
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set redmod 1
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set redmod 2
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set redmod 3
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set redmod 4
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set redmod 5
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set AQM_scheme PI
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
set AQM_scheme CoDel
set num_ftp_fwd 1
set num_ftp_fwd 3
set num_ftp_fwd 5
set num_ftp_fwd 7
set num_ftp_fwd 10
set num_ftp_fwd 15
set num_ftp_fwd 20
set num_ftp_fwd 30
set num_ftp_fwd 60
set num_ftp_fwd 100
set num_ftp_fwd 150
set num_ftp_fwd 200
set num_ftp_fwd 300
set num_ftp_fwd 400
set num_ftp_fwd 500
set num_ftp_fwd 700
set num_ftp_fwd 800
set num_ftp_fwd 900
set num_ftp_fwd 1000
