#ifndef __IPSCHEDULER_USER_H_
#define __IPSCHEDULER_USER_H_

#include <omnetpp.h>
#include <omnetpp/cmodule.h>

#include "ipsched/msg/IpPacket_m.h"

using namespace omnetpp;

class User: public cSimpleModule {
private:
    cMessage *readyToSendMessage;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual IpPacket* generateIpPacket();
};

#endif
