#include "ipsched/src/Queue.h"

Define_Module(Queue);

void Queue::initialize() {
    if (getName() == "nrtLpQueue") {
        nrtLpQueueLengthSignal = registerSignal("nrtLpQueueLength");
        emit(nrtLpQueueLengthSignal, queue.getLength());
    } else if (getName() == "nrtHpQueue") {
        nrtHpQueueLengthSignal = registerSignal("nrtHpQueueLength");
        emit(nrtHpQueueLengthSignal, queue.getLength());
    } else if (getName() == "rtLpQueue") {
        rtLpQueueLengthSignal = registerSignal("rtLpQueueLength");
        emit(rtLpQueueLengthSignal, queue.getLength());
    } else if (getName() == "rtHpQueue") {
        rtHpQueueLengthSignal = registerSignal("rtHpQueueLength");
        emit(rtHpQueueLengthSignal, queue.getLength());
    }

    lengthLoggingRate = par("queueLengthLoggingRate").intValue();
}

void Queue::handleMessage(cMessage *msg) {
    if (!strcmp(msg->getName(), "schedulerMessage")) {
        delete msg;

        EV << getName() << ": sending " << msg->getName() << "\n";
        cPacket *packet = (cPacket*) queue.pop();
        onDeparture(packet);
    } else {
        onArrival(msg);
        queue.insert((cPacket*) msg);
        if (simTime().inUnit(SIMTIME_US) % lengthLoggingRate == 0) {
            if (getName() == "nrtLpQueue") {
                emit(nrtLpQueueLengthSignal, queue.getLength());
            } else if (getName() == "nrtHpQueue") {
                emit(nrtHpQueueLengthSignal, queue.getLength());
            } else if (getName() == "rtLpQueue") {
                emit(rtLpQueueLengthSignal, queue.getLength());
            } else if (getName() == "rtHpQueue") {
                emit(rtHpQueueLengthSignal, queue.getLength());
            }
        }
    }
}

long Queue::getLength() {
    return queue.getLength();
}

void Queue::onArrival(cMessage *msg) {
    EV << getName() << ": received " << msg->getName() << "\n";
}

void Queue::onDeparture(cMessage *msg) {
    EV << getName() << " sent " << msg->getName() << "\n";

    send(msg, "out");
}
