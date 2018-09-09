//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.examples.bufferbloat.mod_dumbell_2;

import inet.nodes.inet.Router;
import inet.nodes.inet.StandardHost;
import inet.nodes.inet.StandardHostWithDLThruputMeter;
import inet.nodes.wireless.WirelessAPWithEthPPP;
import inet.nodes.wireless.WirelessHost;
import ned.DatarateChannel;

//
// TODO auto-generated type
//
network Wirelessv1
{
    parameters:
        @display("bgb=512,413");
    types:
        channel fast extends DatarateChannel
        {
            datarate = 1000Mbps;
            delay = 1us;
        }
        channel slow extends DatarateChannel
        {
            datarate = 2Mbps;
            delay = 20ms;
        }
    submodules:
        wirelessap1: WirelessAPWithEthPPP {
            @display("p=196,153");
        }
        wirelesshost1: WirelessHost {
            @display("p=64,53");
        }
        wirelesshost2: WirelessHost {
            @display("p=64,248");
        }
        server1: StandardHostWithDLThruputMeter {
            @display("p=476,154;i=device/server");
        }
        wiredhost1: StandardHost {
            @display("p=196,34");
        }
        wirelessap2: WirelessAPWithEthPPP {
            @display("p=346,153");
        }
    connections:
        wiredhost1.pppg++ <--> fast <--> wirelessap1.pppg++;
        wirelessap1.pppg++ <--> slow { @display("t=2Mbps,t,red"); } <--> wirelessap2.pppg++;
        wirelessap2.pppg++ <--> fast { @display("t=1000Mbps,t"); } <--> server1.pppg++;

}
