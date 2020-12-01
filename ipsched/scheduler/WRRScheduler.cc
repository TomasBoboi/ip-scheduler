#include "WRRScheduler.h"

#include "ipsched/src/Queue.h"

Define_Module(WRRScheduler);

WRRScheduler::WRRScheduler()
{
    readyToScheduleMessage = nullptr;
}

WRRScheduler::~WRRScheduler()
{
    cancelAndDelete(readyToScheduleMessage);
}

void WRRScheduler::initialize()
{
    lastServed_nrtLp = simTime();
    lastServed_nrtHp = simTime();
    lastServed_rtLp = simTime();
    lastServed_rtHp = simTime();

    readyToScheduleMessage = new cMessage("RTSch");

    scheduleAt(simTime(), readyToScheduleMessage);
}

void WRRScheduler::handleMessage(cMessage *msg)
{
    if (msg == readyToScheduleMessage)
    {
        simtime_t firstTime = getMinimumTime(lastServed_nrtLp, lastServed_nrtHp,
                                             lastServed_rtLp, lastServed_rtHp);
        bool sent = false;

        if (firstTime == lastServed_nrtLp)
        {
            if (getQueueLength("nrtLpQueue") > 0)
            {
                send(new cMessage("schedulerMessage"), "nrtLpQueueControl_out");
                sent = true;
            }
            lastServed_nrtLp = simTime();
        }
        else if (firstTime == lastServed_nrtHp)
        {
            if (getQueueLength("nrtHpQueue") > 0)
            {
                send(new cMessage("schedulerMessage"), "nrtHpQueueControl_out");
                sent = true;
            }
            lastServed_nrtHp = simTime();
        }
        else if (firstTime == lastServed_rtLp)
        {
            if (getQueueLength("rtLpQueue") > 0)
            {
                send(new cMessage("schedulerMessage"), "rtLpQueueControl_out");
                sent = true;
            }
            lastServed_rtLp = simTime();
        }
        else if (firstTime == lastServed_rtHp)
        {
            if (getQueueLength("rtHpQueue") > 0)
            {
                send(new cMessage("schedulerMessage"), "rtHpQueueControl_out");
                sent = true;
            }
            lastServed_rtHp = simTime();
        }

        if (!sent)
        {
            scheduleAt(simTime(), readyToScheduleMessage);
        }
    }
    else
    {
        send(msg, "out");

        scheduleAt(
            gate("out")->getTransmissionChannel()->getTransmissionFinishTime(),
            readyToScheduleMessage);
    }
}

simtime_t WRRScheduler::getMinimumTime(simtime_t time1, simtime_t time2,
                                              simtime_t time3, simtime_t time4)
{
    return std::min(std::min(time1, time2), std::min(time3, time4));
}

int WRRScheduler::getQueueLength(const char *queueName)
{
    int queueLength;

    Queue *queue = check_and_cast<Queue *>(
        getParentModule()->getSubmodule(queueName));
    queueLength = queue->getQueueLength();

    EV << queue->getName() << " length: " << queueLength << "\n";

    return queueLength;
}
