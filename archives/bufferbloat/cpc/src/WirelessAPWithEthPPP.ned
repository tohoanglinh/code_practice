//
// Copyright (C) 2006 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

// Add PPP interface by LINH TO

package inet.nodes.wireless;

import inet.base.NotificationBoard;
import inet.mobility.NullMobility;
import inet.linklayer.ethernet.EtherMAC;
import inet.linklayer.etherswitch.MACRelayUnit;
import inet.linklayer.ieee80211.Ieee80211NicAP;
import inet.linklayer.ppp.PPPInterface;


//
// Models a 802.11 Access Point with Ethernet ports.
// It can be used in conjunction with WirelessHost, or any other host model
// containing WirelessNicSTA.
//
// @see WirelessAP, WirelessAPSimplified, WirelessAPWithEth, WirelessAPWithEthSimplified
// @see WirelessHost, WirelessHostSimplified
// @see MobileHost, MFMobileHost
//
module WirelessAPWithEthPPP
{
    parameters:
        @node();
        @labels(node,ethernet-node,wireless-node);
        @display("i=device/accesspoint;bgb=488,403");
        string relayUnitType = default("MACRelayUnitNP"); // type of the MACRelayUnit (MACRelayUnitNP, MACRelayUnitPP, etc)
    gates:
        inout pppg[] @labels(PPPFrame-conn);        
        input radioIn @directIn;
        inout ethg[] @labels(EtherFrame-conn);
    submodules:
        relayUnit: <relayUnitType> like MACRelayUnit {
            parameters:
                @display("p=303,113");
            gates:
                lowerLayerIn[sizeof(ethg)+1];
                lowerLayerOut[sizeof(ethg)+1];
        }
        wlan: Ieee80211NicAP { // see also Ieee80211NicAPSimplified
            parameters:
                @display("p=55,248;q=queue");
        }
        eth[sizeof(ethg)]: EtherMAC {
            parameters:
                promiscuous = true;
                txQueueLimit = 1000; // increase if needed
                queueModule = "";
                @display("p=383,238,row;q=queue");
        }
        ppp[sizeof(pppg)]: PPPInterface {
            parameters:
                @display("p=215,287,row,110;q=l2queue");
        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=78,60");
        }
        mobility: NullMobility {
            parameters:
                @display("p=71,121");
        }
    connections allowunconnected:
        radioIn --> { @display("m=s"); } --> wlan.radioIn;
        wlan.uppergateIn <-- relayUnit.lowerLayerOut[0];
        wlan.uppergateOut --> relayUnit.lowerLayerIn[0];
        for i=0..sizeof(ethg)-1 {
            eth[i].upperLayerIn <-- relayUnit.lowerLayerOut[i+1];
            eth[i].upperLayerOut --> relayUnit.lowerLayerIn[i+1];
            eth[i].phys <--> ethg[i];
        }
        // connections to network outside
        for i=0..sizeof(pppg)-1 {
            pppg[i] <--> ppp[i].phys;
            ppp[i].netwIn <-- relayUnit.lowerLayerOut[i];
            ppp[i].netwOut --> relayUnit.lowerLayerIn[i];
        }        
}

