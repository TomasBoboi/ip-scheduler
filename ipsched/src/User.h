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

#ifndef __IPSCHEDULER_USER_H_
#define __IPSCHEDULER_USER_H_

#include <omnetpp.h>
#include <omnetpp/cmodule.h>
#include <string>

#include "ipsched/msg/IpPacket_m.h"

using namespace omnetpp;

class User: public cSimpleModule {
protected:
    static const unsigned char USER_LOW_NRT_PRIO = 0u;
    static const unsigned char USER_HIGH_NRT_PRIO = 1u;
    static const unsigned char USER_LOW_RT_PRIO = 2u;
    static const unsigned char USER_HIGH_RT_PRIO = 3u;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual IpPacket* generateIpPacket();
    unsigned char getUserPriority();
};

#endif
