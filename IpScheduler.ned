network IpScheduler
{
    parameters:
        int nrtLpUserNo;
        int nrtHpUserNo;
        int rtLpUserNo;
        int rtHpUserNo;
    
    submodules:
        nrtLpUsers[nrtLpUserNo]: User {

            @display("p=72,65;i=block/users");
        }
        nrtHpUsers[nrtHpUserNo]: User {

            @display("p=72,147;i=block/users");
        }
        rtLpUsers[rtLpUserNo]: User {

            @display("i=block/users;p=72,225");
        }
        rtHpUsers[rtHpUserNo]: User {

            @display("i=block/users;p=72,308");
        }

        packetHandler: PacketHandler {

            @display("p=360,186;i=abstract/dispatcher");
        }

        sink: Sink {

            @display("i=block/sink;p=538,186");
        }

    connections:
        for i=0..nrtLpUserNo - 1 {
            nrtLpUsers[i].out --> packetHandler.nrtLp_in;
        }
        for i=0..nrtHpUserNo - 1 {
            nrtHpUsers[i].out --> packetHandler.nrtHp_in;
        }
        for i=0..rtLpUserNo - 1 {
            rtLpUsers[i].out --> packetHandler.rtLp_in;
        }
        for i=0..rtHpUserNo - 1 {
            rtHpUsers[i].out --> packetHandler.rtHp_in;
        }

        packetHandler.out --> sink.in;
}
