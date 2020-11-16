network IpScheduler
{
    parameters:
        int nrtLpUsersNo;
        int nrtHpUsersNo;
        int rtLpUsersNo;
        int rtHpUsersNo;

        @display("bgb=617,386");
    submodules:
        nrtLpUsers[nrtLpUsersNo]: User {

            @display("p=106,65;i=block/users");
        }
        nrtHpUsers[nrtHpUsersNo]: User {

            @display("p=106,147;i=block/users");
        }
        rtLpUsers[rtLpUsersNo]: User {

            @display("i=block/users;p=106,225");
        }
        rtHpUsers[rtHpUsersNo]: User {

            @display("i=block/users;p=106,308");
        }

        packetHandler: PacketHandler {

            @display("p=394,186;i=abstract/dispatcher");
        }

        sink: Sink {

            @display("i=block/sink;p=572,186");
        }

    connections:
        for i=0..nrtLpUsersNo - 1 {
            nrtLpUsers[i].out --> packetHandler.nrtLp_in++;
        }
        for i=0..nrtHpUsersNo - 1 {
            nrtHpUsers[i].out --> packetHandler.nrtHp_in++;
        }
        for i=0..rtLpUsersNo - 1 {
            rtLpUsers[i].out --> packetHandler.rtLp_in++;
        }
        for i=0..rtHpUsersNo - 1 {
            rtHpUsers[i].out --> packetHandler.rtHp_in++;
        }

        packetHandler.out --> sink.in;
}
