#include "sender_receiver.h"

BroadcastSenderReceiver::BroadcastSenderReceiver():
    Broadcaster(),
    BroadcastReceiver()
{}

void SenderReceiverLoop(BroadcastSenderReceiver*);
void BroadcastSenderReceiver::StartDoingStuff()
{
    static std::thread activityThread(SenderReceiverLoop, this);
}

bool BroadcastSenderReceiver::CompareSenderReceiverSockaddrSame(){
    sockaddr_in mySender = Broadcaster::scAddr;
    sockaddr_in otherSender = BroadcastReceiver::scAddrSender;

    return 
        mySender.sin_addr.S_un.S_addr == otherSender.sin_addr.S_un.S_addr
        &&
        mySender.sin_port == otherSender.sin_port
        ;
}
