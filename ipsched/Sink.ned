package ipsched;

simple Sink
{
    parameters:
        // we collect statistics about the packets
        // packet lifetime (the time it takes for a packet to reach the sink
        @signal[packetLifetime](type="simtime_t");
        @statistic[packetLifetime](title="IP Packet lifetime"; unit=us; record=vector,mean,min,max);
        // the total number of packets that reach the sink
        @signal[numberOfPackets](type="long");
        @statistic[numberOfPackets](title="IP Packet Count"; record=count);
    // end:parameters

    gates:
        // main input, where the packets enter
        input in;
    // end:gates
}
