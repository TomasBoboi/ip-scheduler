package ipsched;

module PacketHandler
{
    parameters:
        int nrtLpUsersNo;
        int nrtHpUsersNo;
        int rtLpUsersNo;
        int rtHpUsersNo;
        double ipChannelDatarate @unit(Mbps);

        @signal[nrtLpQueueLength](type="long");
        @statistic[nrtLpQueueLength](title="NRT_LP Queue Length"; source="nrtLpQueueLength"; record=vector,stats);

        @signal[nrtHpQueueLength](type="long");
        @statistic[nrtHpQueueLength](title="NRT_HP Queue Length"; source="nrtHpQueueLength"; record=vector,stats);

        @signal[rtLpQueueLength](type="long");
        @statistic[rtLpQueueLength](title="RT_LP Queue Length"; source="rtLpQueueLength"; record=vector,stats);

        @signal[rtHpQueueLength](type="long");
        @statistic[rtHpQueueLength](title="RT_HP Queue Length"; source="rtHpQueueLength"; record=vector,stats);

    gates:
        input nrtLp_in[];
        input nrtHp_in[];
        input rtLp_in[];
        input rtHp_in[];
        output out;

    types:
        channel PacketChannel extends ned.DatarateChannel
        {
            datarate = ipChannelDatarate;
        }

    submodules:
        scheduler: Scheduler {
            @display("i=block/dispatch;p=249,192");
        }

        nrtLpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,303");
        }
        nrtHpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,231");
        }
        rtLpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,153");
        }
        rtHpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,73");
        }

    connections:
        for i=0..nrtLpUsersNo - 1 {
            nrtLp_in[i] --> nrtLpQueue.in++;
        }
        for i=0..nrtHpUsersNo - 1 {
            nrtHp_in[i] --> nrtHpQueue.in++;
        }
        for i=0..rtLpUsersNo - 1 {
            rtLp_in[i] --> rtLpQueue.in++;
        }
        for i=0..rtHpUsersNo - 1 {
            rtHp_in[i] --> rtHpQueue.in++;
        }

        nrtLpQueue.out --> PacketChannel --> scheduler.in++;
        nrtHpQueue.out --> PacketChannel --> scheduler.in++;
        rtLpQueue.out --> PacketChannel --> scheduler.in++;
        rtHpQueue.out --> PacketChannel --> scheduler.in++;

        scheduler.out --> out;
}
