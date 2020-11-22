#ifndef __IPSCHEDULER_USER_H_
#define __IPSCHEDULER_USER_H_

#include <omnetpp.h>
#include <omnetpp/cmodule.h>
#include <string>

#include "ipsched/msg/IpPacket_m.h"

using namespace omnetpp;

class User: public cSimpleModule {
protected:
    static const unsigned char USER_LOW_NRT_PRIO = 0u;
    static const unsigned char USER_HIGH_NRT_PRIO = 1u;
    static const unsigned char USER_LOW_RT_PRIO = 2u;
    static const unsigned char USER_HIGH_RT_PRIO = 3u;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual IpPacket* generateIpPacket();
    unsigned char getUserPriority();
};

#endif
