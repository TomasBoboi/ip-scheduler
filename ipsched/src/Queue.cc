#include "ipsched/src/Queue.h"

Define_Module(Queue);

void Queue::initialize() {
    // TODO - Generated method body
}

void Queue::handleMessage(cMessage *msg) {
    EV << "Queue: received a message\n";
    delete msg;
}
