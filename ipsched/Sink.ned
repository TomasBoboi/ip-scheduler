package ipsched;

simple Sink
{
    parameters:
        @signal[packetLifetime](type="simtime_t");
        @statistic[packetLifetime](title="IP Packet lifetime"; unit=us; record=vector,mean,min,max);

        @signal[numberOfPackets](type="long");
        @statistic[numberOfPackets](title="IP Packet Count"; record=count);

    gates:
        input in;
}
