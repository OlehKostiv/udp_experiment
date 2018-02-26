#include "global_stuff.h"
#include "broadcast_receiver.h"

#include <string>
#include <exception>
#include <iostream>

using std::exception;
using std::string;

BroadcastReceiver& BroadcastReceiver::get_instance() {
    static BroadcastReceiver instance;
    return instance;
}

BroadcastReceiver::BroadcastReceiver():
    BasicBroadcastReceiver()
{
    WSAstartup();
    InitializeSockaddr();
    CreateSocket();
    SetSocketOptions();
    BindSocket();
}

void BroadcastReceiver::WSAstartup(){
    if (int error = WSAStartup(MAKEWORD(2, 2), &wsadata)) {
        ErrorMessage("Receiver WSAStartup failed", error);
    }
    else
        ErrorMessage("Receiver WSAStartup succeeded");
}

void BroadcastReceiver::InitializeSockaddr() {
    scAddr = sockaddr_in{};
    
    scAddr.sin_family = AF_INET;
    scAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    scAddr.sin_port = htons(port);

    scAddrPtr = reinterpret_cast<sockaddr*>(&scAddr);
    scAddrSize = sizeof(scAddr);

    scAddrPtrSender = reinterpret_cast<sockaddr*>(&scAddrSender);
    scAddrSenderSize = sizeof(scAddrSender);
}

void BroadcastReceiver::CreateSocket() {
    sc = socket(AF_INET, SOCK_DGRAM, NULL);
    if (sc == SOCKET_ERROR)
        ErrorMessage("Receiver failed to create socket", GetLastError());
    else
        ErrorMessage("Receiver socket created");
}

void BroadcastReceiver::BindSocket() {
    if (bind(sc, scAddrPtr, scAddrSize) == SOCKET_ERROR)
        ErrorMessage("Receiver failed to bind socket", GetLastError());
    else
        ErrorMessage("Receiver socket bound");
}

void BroadcastReceiver::CloseSocket(){
    if (closesocket(sc))
        ErrorMessage("Receiver failed to close socket", GetLastError());
    else
        ErrorMessage("Receiver closed socket");
}

void BroadcastReceiver::SetSocketOptions(){
    setsockopt(sc, SOL_SOCKET, SO_REUSEADDR, (char*)&scOptions, sizeof(int));
}

void ReceivingLoop(BroadcastReceiver *);
void BroadcastReceiver::StartReceivingThread() {
    bcastReceivingThread = std::thread(ReceivingLoop, this);
}

std::string BroadcastReceiver::ReceiveBroadcastedMessage()
{
    std::string buff(100, 0);

    if (recvfrom(sc, &buff.front(), buff.capacity(), NULL, scAddrPtrSender, &scAddrSenderSize) == SOCKET_ERROR)
        ErrorMessage("failed to recv message", GetLastError());
    else
        ErrorMessage(buff);

    string inetInfo(inet_ntoa(scAddrSender.sin_addr));

    buff.shrink_to_fit();
    return inetInfo + ": " + buff;
}
void BroadcastReceiver::StopReceiving() {
    //bc_receiving.~thread(); 
}

BroadcastReceiver::~BroadcastReceiver()
{
    CloseSocket();
}
