package ipsched;

simple Sink
{
    parameters:
        @signal[packetLifetime](type="simtime_t");
        @statistic[packetLifetime](title="IP Packet lifetime"; unit=us; record=vector,mean,max);
    
    gates:
        input in;
}
