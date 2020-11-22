#ifndef __IPSCHEDULER_SINK_H_
#define __IPSCHEDULER_SINK_H_

#include <omnetpp.h>

using namespace omnetpp;

class Sink: public cSimpleModule {
private:
    simsignal_t packetLifetimeSignal;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
