#include "ipsched/src/User.h"

Define_Module(User);

void User::initialize() {
    readyToSendMessage = new cMessage("RTS");

    scheduleAt(simTime(), readyToSendMessage);
}

void User::handleMessage(cMessage *msg) {
    if (msg == readyToSendMessage) {
        IpPacket *ipPacket = generateIpPacket();
        send(ipPacket, "out");

        scheduleAt(
                simTime()
                        + SimTime(uniform(1, 10), SimTimeUnit::SIMTIME_US).trunc(
                                SimTimeUnit::SIMTIME_US), readyToSendMessage);

        EV << getName() << ":\tsent message";
    }
}

IpPacket* User::generateIpPacket() {
    IpPacket *ipPacket = new IpPacket("IP_PACKET");

    ipPacket->setByteLength(par("ipPacketSize").intValue());

    EV << getName() << ":\tgenerated packet of " << ipPacket->getByteLength()
              << " bytes\n";

    return ipPacket;
}
