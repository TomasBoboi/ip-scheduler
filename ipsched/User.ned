package ipsched;

simple User
{
    parameters:
        int nrtLpUsersNo;
        int nrtHpUsersNo;
        int rtLpUsersNo;
        int rtHpUsersNo;
        int ipPacketSize @unit(B);

    gates:
        output out;
}
