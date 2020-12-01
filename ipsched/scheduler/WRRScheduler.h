#ifndef __IPSCHEDULER_WRRSCHEDULER_H_
#define __IPSCHEDULER_WRRSCHEDULER_H_

#include <omnetpp.h>

using namespace omnetpp;

class WRRScheduler : public cSimpleModule
{
public:
    WRRScheduler();
    ~WRRScheduler();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual int getQueueLength(const char *name);
    simtime_t getMinimumTime(simtime_t time1, simtime_t time2, simtime_t time3,
                             simtime_t time4);

private:
    cMessage *readyToScheduleMessage;

    simtime_t lastServed_nrtLp;
    simtime_t lastServed_nrtHp;
    simtime_t lastServed_rtLp;
    simtime_t lastServed_rtHp;
};

#endif
