//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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
