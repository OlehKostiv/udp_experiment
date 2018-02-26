#pragma once
#include "global_stuff.h"
#include "basic_socketed_entity.h"

#include <thread>


class BasicBroadcastReceiver:
    protected BasicSocketedEntityFunctionality
{
protected:
    virtual void BindSocket() = 0;
    virtual void StartReceivingThread() = 0;
    virtual void StopReceiving() = 0;
};

struct BroadcastReceiverData:
    protected BasicSocketedEntityData
{
protected:    
    sockaddr_in scAddrSender;
    sockaddr* scAddrPtrSender;
    int scAddrSenderSize;  
    std::thread bcastReceivingThread; 
};

class BroadcastReceiver :
    public BasicBroadcastReceiver,
    protected BroadcastReceiverData
{
public:
    static BroadcastReceiver& get_instance();

    virtual void StartReceivingThread() override;
    virtual std::string ReceiveBroadcastedMessage();
    virtual void StopReceiving() override;
protected:
    virtual void WSAstartup() override;
    virtual void InitializeSockaddr() override;
    virtual void CreateSocket() override;
    virtual void BindSocket() override;
    virtual void CloseSocket() override;
    virtual void SetSocketOptions() override;
protected:
    BroadcastReceiver();
    ~BroadcastReceiver(); 
};
