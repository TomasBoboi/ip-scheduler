#include "ipsched/src/Sink.h"

Define_Module(Sink);

void Sink::initialize() {
    packetLifetimeSignal = registerSignal("packetLifetime");
    numberOfPacketsSignal = registerSignal("numberOfPacketsSignal");
}

void Sink::handleMessage(cMessage *msg) {
    simtime_t packetLifetime = simTime() - msg->getCreationTime();
    long numberOfPackets = 1;

    EV << "SINK: received " << msg->getName() << "from " << msg->getSenderModule()->getName() << "\n";
    EV << "      packet lifetime: "
              << packetLifetime.inUnit(SimTimeUnit::SIMTIME_US) << "us\n";

    emit(packetLifetimeSignal, packetLifetime);
    emit(numberOfPacketsSignal, numberOfPackets);

    delete msg;
    EV << "      deleted successfully\n";
}
