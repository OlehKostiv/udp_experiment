#pragma once
#include "global_stuff.h"
#include <afxsock.h>
#include <winsock2.h>

class BasicSocketedEntityFunctionality {
protected:
    virtual void WSAstartup()  = 0;
    virtual void InitializeSockaddr() = 0; 
    virtual void CreateSocket() = 0;
    virtual void CloseSocket() = 0;
    virtual void SetSocketOptions() = 0;
};

struct BasicSocketedEntityData {
protected:
    WSADATA wsadata;

    sockaddr_in scAddr;
    sockaddr* scAddrPtr;
    int scAddrSize;  
    SOCKET sc; 

    int scOptions = 1;
};
