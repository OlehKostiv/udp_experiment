#include <iostream>

using namespace std;

#include "broadcaster.h"
#include "broadcast_receiver.h"
#include "sender_receiver.h"

/*
    server part
        receive broadcast
        get client data
        save client data
        start communication with client

    client part
        broadcast
        get response
        save server data
*/
bool tracingErrors = false;

int main() 
try{
    /*BroadcastReceiver& bcastRec = BroadcastReceiver::get_instance();
    bcastRec.StartReceivingThread();

    Broadcaster bcastSen;
    bcastSen.StartSending();*/

    BroadcastSenderReceiver bro;
    bro.StartDoingStuff();

    while (1) {};
    return 0;
}
catch(exception& ex){
    cout << ex.what() << endl;
    system("pause");
    return 0;
}