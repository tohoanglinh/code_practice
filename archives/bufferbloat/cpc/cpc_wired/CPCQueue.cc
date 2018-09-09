// Copyright (C) 2014-2015 Hoang-Linh TO
// Based on DropTailQueue, REDQueue (A. Varga), CoDelQueue (C. Mehlis, K.Nichols and V.Jacobson)
// Developed from: 2014-05-14
// CPCQueue - Cascade Predict Controlled Queue

#include <omnetpp.h> //fixed
#include "CPCQueue.h" //fixed

Define_Module(CPCQueue);

void CPCQueue::initialize()
{
    PassiveQueueBase::initialize();
    queue.setName("l2queue");

    avgQlenVec.setName("avg queue length");
    qlenVec.setName("queue length");
    dropVec.setName("drops");

    outGate = gate("out");

    // configuration
    buffersize = par("buffersize");
}

bool CPCQueue::enqueue(cMessage *msg)
{
    if (buffersize && queue.length() >= buffersize)
    {
        EV << "Queue is getting full, dropping packet.\n";
        delete msg;
        dropVec.record(1);
        return true;
    }
    else
    {
        queue.insert(msg);
        qlenVec.record(queue.length());
        return false;
    }
}

cMessage *CPCQueue::dequeue()
{
    if (queue.empty())
        return NULL;
    cMessage *pk = (cMessage *)queue.pop();

    //statistics
    qlenVec.record(queue.length());

    return pk;
}

void CPCQueue::sendOut(cMessage *msg)
{
    PassiveQueueBase::send(msg, outGate);
}

void CPCQueue::finish()
{
    PassiveQueueBase::finish();
}
