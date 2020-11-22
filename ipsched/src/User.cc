#include "ipsched/src/User.h"

Define_Module(User);

void User::initialize() {
    scheduleAt(simTime(), generateIpPacket());
}

void User::handleMessage(cMessage *msg) {
    send(generateIpPacket(), "out");

    scheduleAt(
            simTime() + SimTime(exponential(0.5), SIMTIME_US).trunc(SIMTIME_US),
            msg);
}

IpPacket* User::generateIpPacket() {
    IpPacket *ipPacket = new IpPacket("IP_PACKET");

    ipPacket->setByteLength(par("ipPacketSize").intValue());

    unsigned char userPrio = getUserPriority();
    switch (userPrio) {
    case User::USER_LOW_NRT_PRIO:
        EV << "NRT_LP_USER: ";
        break;
    case User::USER_HIGH_NRT_PRIO:
        EV << "NRT_HIGH_USER: ";
        break;
    case User::USER_LOW_RT_PRIO:
        EV << "RT_LOW_USER: ";
        break;
    case User::USER_HIGH_RT_PRIO:
        EV << "RT_HIGH_USER: ";
        break;
    }

    EV << "generated packet of " << ipPacket->getByteLength() << " bytes\n";

    return ipPacket;
}

unsigned char User::getUserPriority() {
    for (int index = 0; index < par("nrtLpUsersNo").intValue(); index++) {
        std::string path = std::string("^.nrtLpUsers[");
        path = path.append(std::__cxx11::to_string(index));
        path = path.append("]");

        cModule *currentUser = getModuleByPath(path.c_str());
        if (currentUser == this) {
            return USER_LOW_NRT_PRIO;
        }
    }

    for (int index = 0; index < par("nrtHpUsersNo").intValue(); index++) {
        std::string path = std::string("^.nrtHpUsers[");
        path = path.append(std::__cxx11::to_string(index));
        path = path.append("]");

        cModule *currentUser = getModuleByPath(path.c_str());
        if (currentUser == this) {
            return USER_HIGH_NRT_PRIO;
        }
    }
    for (int index = 0; index < par("rtLpUsersNo").intValue(); index++) {
        std::string path = std::string("^.rtLpUsers[");
        path = path.append(std::__cxx11::to_string(index));
        path = path.append("]");

        cModule *currentUser = getModuleByPath(path.c_str());
        if (currentUser == this) {
            return USER_LOW_RT_PRIO;
        }
    }
    for (int index = 0; index < par("rtHpUsersNo").intValue(); index++) {
        std::string path = std::string("^.rtHpUsers[");
        path = path.append(std::__cxx11::to_string(index));
        path = path.append("]");

        cModule *currentUser = getModuleByPath(path.c_str());
        if (currentUser == this) {
            return USER_HIGH_RT_PRIO;
        }
    }

    return USER_LOW_NRT_PRIO;
}
