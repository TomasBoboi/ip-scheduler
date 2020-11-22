#include "ipsched/src/Sink.h"

Define_Module(Sink);

void Sink::initialize() {
    packetLifetimeSignal = registerSignal("packetLifetime");
}

void Sink::handleMessage(cMessage *msg) {
    simtime_t packetLifetime = simTime() - msg->getCreationTime();

    EV << "SINK: received " << msg->getName() << "\n";
    EV << "      packet lifetime: "
              << packetLifetime.inUnit(SimTimeUnit::SIMTIME_US) << "us\n";

    emit(packetLifetimeSignal, packetLifetime);

    delete msg;
    EV << "      deleted successfully\n";
}
