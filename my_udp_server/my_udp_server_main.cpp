#include <iostream>
#include <afxsock.h>
//#include <afxtempl.h>
#include <winsock2.h>
#include <thread>
#include <chrono>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::this_thread::sleep_for;
using std::system;

constexpr int port = 8888;

int main() {
    WSADATA wsadata{};
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    sockaddr_in sc_addr{};
    sockaddr* sc_addr_ptr = reinterpret_cast<sockaddr*>(&sc_addr);
    unsigned sc_addr_size = sizeof(sc_addr);
    sc_addr.sin_family = AF_INET;
    sc_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    sc_addr.sin_port = htons(port);
    
    SOCKET sc = socket(AF_INET, SOCK_DGRAM, NULL);

    if (sc == SOCKET_ERROR) {
        cerr<< "failed to create socket, error: " 
            << GetLastError() 
            << endl;
        return system("pause");
    }else 
        cout << "socket created" << endl;

    if(bind(sc, sc_addr_ptr, sc_addr_size) == SOCKET_ERROR){
        cerr<< "failed to bind socket, error: " 
            << GetLastError() 
            << endl;
        return system("pause");
    }else 
        cout << "socket bound" << endl;
    
    //for (int i = 0; i < 10; ++i)
    while(1)
    {
        char buff[100]{};       
        sockaddr_in sender;
        sockaddr* sender_ptr = reinterpret_cast<sockaddr*>(&sender);
        int sender_size = sizeof(sender);

        if (recvfrom(sc, buff, sizeof(buff), NULL, sender_ptr, &sender_size) == SOCKET_ERROR)
            cerr<< "failed to recv message, error: " 
                << GetLastError()
                << endl;
        
        else cout << buff << endl;
        
        sleep_for(std::chrono::seconds(1));
    }
    closesocket(sc);
    WSACleanup();
    return system("pause");
}