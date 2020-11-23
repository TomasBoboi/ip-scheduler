package ipsched;

simple User
{
    parameters:
        // the size of an IP packet, which the user generates
        int ipPacketSize @unit(B);
    // end:parameters

    gates:
        // the main output gate, where the packets are sent to the packet handler
        output out;
    // end:gates
}
