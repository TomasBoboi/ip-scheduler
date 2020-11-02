module PacketHandler
{
    gates:
        input nrtLp_in;
        input nrtHp_in;
        input rtLp_in;
        input rtHp_in;
        output out;
    
    submodules:
        scheduler: Scheduler {
            @display("i=block/dispatch;p=249,192");
        }

        nrtLpQueue: Queue {
            parameters:
                @display("i=block/queue;p=96,303");
                @display("p=106,132");
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
        nrtLp_in --> nrtLpQueue.in;
        nrtHp_in --> nrtHpQueue.in;
        rtLp_in --> rtLpQueue.in;
        rtHp_in --> rtHpQueue.in;

        nrtLpQueue.out --> scheduler.in;
        nrtHpQueue.out --> scheduler.in;
        rtLpQueue.out --> scheduler.in;
        rtHpQueue.out --> scheduler.in;

        scheduler.out --> out;
}
