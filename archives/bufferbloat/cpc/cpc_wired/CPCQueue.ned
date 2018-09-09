// Copyright (C) 2014-2015 Hoang-Linh TO
// Based on DropTailQueue, REDQueue (A. Varga), CoDelQueue (C. Mehlis, K.Nichols and V.Jacobson)
// Developed from: 2014-05-14
// CPCQueue - Cascade Predict Controlled Queue

package inet.networklayer.queue; // fixed

simple CPCQueue like OutputQueue
{
	parameters:
	    // additional parameters. For ex, buffersize
		int buffersize = default(500);
		
	    @display("i=block/queue");
	gates:
		input in;
		output out;
}