#pragma once
#include "global_stuff.h"
#include "basic_socketed_entity.h"
#include <thread>

class BasicBroadcaster :
    protected BasicSocketedEntityFunctionality
{
protected:
    virtual void StartSending() = 0;
    virtual void StopSending() = 0;
};

struct BasicBroadcasterData:
    protected BasicSocketedEntityData
{
protected:
    std::thread bcastSendingThread;
};

class Broadcaster :
    protected BasicBroadcaster,
    protected BasicBroadcasterData
{
public:
    Broadcaster();
    ~Broadcaster();
    virtual void StartSending() override;
    virtual void SendBroadcastMessage(const std::string&);
    virtual void StopSending() override;
protected:
    virtual void WSAstartup() override;
    virtual void InitializeSockaddr() override;
    virtual void CreateSocket() override;
    virtual void SetSocketOptions() override;
    virtual void CloseSocket() override;
};