#ifndef __IPSCHEDULER_QUEUE_H_
#define __IPSCHEDULER_QUEUE_H_

#include <omnetpp.h>

using namespace omnetpp;

class Queue: public cSimpleModule {
private:
    simsignal_t nrtLpQueueLengthSignal;
    simsignal_t nrtHpQueueLengthSignal;
    simsignal_t rtLpQueueLengthSignal;
    simsignal_t rtHpQueueLengthSignal;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
