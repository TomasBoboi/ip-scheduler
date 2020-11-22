#include "ipsched/src/Queue.h"

Define_Module(Queue);

void Queue::initialize() {
    if (getName() == "nrtLpQueue") {
        nrtLpQueueLengthSignal = registerSignal("nrtLpQueueLength");
    } else if (getName() == "nrtHpQueue") {
        nrtHpQueueLengthSignal = registerSignal("nrtHpQueueLength");
    } else if (getName() == "rtLpQueue") {
        rtLpQueueLengthSignal = registerSignal("rtLpQueueLength");
    } else if (getName() == "rtHpQueue") {
        rtHpQueueLengthSignal = registerSignal("rtHpQueueLength");
    }
}

void Queue::handleMessage(cMessage *msg) {
    EV << getName() << " received a message\n";
    delete msg;
}
