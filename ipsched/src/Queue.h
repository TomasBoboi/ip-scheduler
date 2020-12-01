#ifndef __IPSCHEDULER_QUEUE_H_
#define __IPSCHEDULER_QUEUE_H_

#include <omnetpp.h>

using namespace omnetpp;

class Queue: public cSimpleModule {
private:
    int lengthLoggingRate;

protected:
    cPacketQueue queue;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void onArrival(cMessage *msg);
    void onDeparture(cMessage *msg);

    simsignal_t nrtLpQueueLengthSignal;
    simsignal_t nrtHpQueueLengthSignal;
    simsignal_t rtLpQueueLengthSignal;
    simsignal_t rtHpQueueLengthSignal;

public:
    int getQueueLength();
};

#endif
