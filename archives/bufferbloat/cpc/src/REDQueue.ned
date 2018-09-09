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

// Added by To Hoang Linh
// mixim-inet projects
// REDDropper + FIFOQueue = REDQueue
// call: **.ppp[*].queueType = "REDQueue"

package inet.linklayer.queue;
import inet.linklayer.IOutputQueue;

module REDQueue like IOutputQueue
{
    parameters:
        double wq = default(0.002);  // queue weight
        double minth = default(5);  // minimum threshold for avg queue length
        double maxth = default(50);  // maximum threshold for avg queue length (=buffer capacity)
        double maxp = default(0.02);  // maximum value for pb
        string queueName = default("l2queue"); // name of the inner cQueue object, used in the 'q' tag of the display string        
        @display("i=block/queue;bgb=228,116");
    gates:
        input in;
        output out;
    submodules:
        redDropper: REDDropper {
            numGates = 1;
            wq = wq;
            minths = string(minth);
            maxths = string(maxth);
            maxps = string(maxp);
            @display("p=66,56");
        }
        fifoQueue: FIFOQueue {
            queueName = queueName;
            @display("p=176,56");
        }
    connections:
        in --> redDropper.in[0];
        redDropper.out[0] --> fifoQueue.in++;
        fifoQueue.out --> out;
}
