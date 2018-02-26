#include "global_stuff.h"
#include "broadcaster.h"
#include "broadcast_receiver.h"
#include "sender_receiver.h"

#include <iostream>

using namespace std::chrono;
using namespace std::this_thread;
using myClock = steady_clock;

void SendingLoop(Broadcaster* ptr){
    for (auto then = myClock::now(); myClock::now() - then < seconds(60); sleep_for(seconds(1)))
    {
        std::string buff;
        std::cin >> buff;
        ptr->SendBroadcastMessage(buff);  
    }
}

void ReceivingLoop(BroadcastReceiver * ptr){
    for (auto then = myClock::now(); myClock::now() - then < seconds(60); sleep_for(std::chrono::seconds(1)))
    {
        std::string buff = ptr->ReceiveBroadcastedMessage();
        if (buff.size())
            std::cout << "received: " << buff << std::endl;
    }
}

void ReceivingLoop2(BroadcastSenderReceiver* ptr) {
    for (auto then = myClock::now(); myClock::now() - then < seconds(60); sleep_for(std::chrono::seconds(1)))
    {
        std::string buff = ptr->ReceiveBroadcastedMessage();
        if (!buff.size())
            continue;
        if(!ptr->CompareSenderReceiverSockaddrSame())
            std::cout << "received: " << buff << std::endl;
    }
}

void SenderReceiverLoop(BroadcastSenderReceiver* ptr) {
    static std::thread sending(SendingLoop, ptr);
    static std::thread receiving(ReceivingLoop2, ptr);
}

