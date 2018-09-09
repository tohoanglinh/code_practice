// Copyright (C) 2014-2015 Hoang-Linh TO
// Based on DropTailQueue, REDQueue (A. Varga), CoDelQueue (C. Mehlis, K.Nichols and V.Jacobson)
// Developed from: 2014-05-14
// CPCQueue - Cascade Predict Controlled Queue

#ifndef __INET_CPCQUEUE_H
#define __INET_CPCQUEUE_H

#include <omnetpp.h>
#include "PassiveQueueBase.h"

class INET_API CPCQueue : public PassiveQueueBase
{
    protected:
        // configuration
        int buffersize;

        // state
        cQueue queue;
        cGate *outGate;

        // statistics
        cOutVector avgQlenVec; //from RED
        cOutVector qlenVec;
        cOutVector dropVec;

    protected:
        virtual void initialize(); // redefined from PassiveQueueBase
        virtual void finish(); // for record statistics

        virtual bool enqueue(cMessage *msg); // redefined from PassiveQueueBase
        virtual cMessage *dequeue(); // redefined from PassiveQueueBase
        virtual void sendOut(cMessage *msg);
};
#endif /* CPCQUEUE_H_ */
