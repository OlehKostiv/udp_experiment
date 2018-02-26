#pragma once
#include "global_stuff.h"
#include "broadcaster.h"
#include "broadcast_receiver.h"

class BroadcastSenderReceiver :
    public Broadcaster,
    public BroadcastReceiver
{
public:
    BroadcastSenderReceiver();

    void StartDoingStuff();
    bool CompareSenderReceiverSockaddrSame();

    //friend void SenderReceiverLoop(BroadcastSenderReceiver*);
    //friend void ReceivingLoop2(BroadcastSenderReceiver*);
};
