#include "global_stuff.h"
#include "broadcaster.h"

#include <string>
#include <exception>
#include <iostream>

Broadcaster::Broadcaster() 
{
    WSAstartup();
    InitializeSockaddr();
    CreateSocket();
    SetSocketOptions();
}

Broadcaster::~Broadcaster()
{
    CloseSocket();
}

void SendingLoop(Broadcaster*);
void Broadcaster::StartSending()
{
    bcastSendingThread = std::thread(SendingLoop, this);
}

void Broadcaster::SendBroadcastMessage(const std::string& buff)
{
    if (sendto(sc, buff.c_str(), buff.size(), NULL, scAddrPtr, scAddrSize) == SOCKET_ERROR)
        ErrorMessage("Broadcaster failed to send message", GetLastError());
    else
        ErrorMessage("Broadcaster message sent");
}

void Broadcaster::StopSending()
{
}

void Broadcaster::WSAstartup()
{
    if (int error = WSAStartup(MAKEWORD(2, 2), &wsadata)) {
        ErrorMessage("WSAStartup failed", error);
    }
    else
        ErrorMessage("WSAStartup succeeded");
}

void Broadcaster::InitializeSockaddr()
{
    scAddr = sockaddr_in{};
    scAddrPtr = reinterpret_cast<sockaddr*>(&scAddr);
    scAddr.sin_family = AF_INET;
    scAddr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
    scAddr.sin_port = htons(port);
}

void Broadcaster::CreateSocket()
{
    sc = socket(AF_INET, SOCK_DGRAM, NULL);
    if (sc == SOCKET_ERROR)
        ErrorMessage("Broadcaster failed to create socket", GetLastError());
    else
        ErrorMessage("Broadcaster socket created");
}

void Broadcaster::SetSocketOptions(){
    setsockopt(sc, SOL_SOCKET, SO_BROADCAST, (char*)&scOptions, sizeof(int));
}

void Broadcaster::CloseSocket()
{
    if (closesocket(sc))
        ErrorMessage("Broadcaster failed to close socket", GetLastError());
    else
        ErrorMessage("Broadcaster closed socket");
}
