#include "ipsched/src/Scheduler.h"
#include "ipsched/src/Queue.h"

Define_Module(Scheduler);

void Scheduler::initialize() {
    // TODO - Generated method body
}

void Scheduler::handleMessage(cMessage *msg) {
    // TODO - Generated method body
}

long Scheduler::getQueueLength(const char *queueName) {
    return check_and_cast<Queue*>(
            getParentModule()->getSubmodule(queueName)->getModuleByPath(
                    ".queue"))->getLength();
}
