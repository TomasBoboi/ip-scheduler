package ipsched;

simple Queue
{
    parameters:
        // the rate at which the queues log their lengths, in microseconds
        int queueLengthLoggingRate;
    // end:parameters
    
    gates:
        // input gates from the users of a certain category
        input in[];
        // input gate from the scheduler, to control the sending of the IP packets
        input schedulerControl_in;
        // main output gate, to send the packets from the queue to the scheduler
        output out;
    // end:gates
}
