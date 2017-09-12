from scapy.all import *
import sys
# sr(IP(dst=sys.argv[1])/ICMP())

p = sr1(IP(src='192.168.0.250', dst='192.168.0.200', ttl=5)/ICMP())
if p.src == '192.168.0.200':
    print 'echo received'