#include <iostream>
#include <afxsock.h>
//#include <afxtempl.h>
#include <winsock2.h>
#include <thread>
#include <chrono>

//using std::cout;
//using std::cerr;
//using std::cin;
//using std::endl;
//using std::this_thread::sleep_for;
//using std::system;
using namespace std;

char message[] = "HELLLLO, TWARYNA!";
constexpr int port = 8888;

int main() {
    WSADATA wsadata{};
    WSAStartup(MAKEWORD(2,2), &wsadata);

    sockaddr_in sc_addr{};
    sockaddr* sc_addr_ptr = reinterpret_cast<sockaddr*>(&sc_addr);
    sc_addr.sin_family = AF_INET;
    sc_addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
    sc_addr.sin_port = htons(port);

    SOCKET sc = socket(AF_INET, SOCK_DGRAM, NULL);

    if (sc == SOCKET_ERROR) {
        cerr<< "failed to create socket, error: " 
            << GetLastError() 
            << endl;
        return system("pause");
    }
    else 
        cout<< "socket created" << endl;
    
    int snds = 1;
    setsockopt(sc, SOL_SOCKET, SO_BROADCAST, (char*)&snds, sizeof(int));

    //for (int i = 0; i < 10; ++i) 
    while(1)
    {
        if (sendto(sc, message, strlen(message), NULL, sc_addr_ptr, sizeof(sc_addr)) == SOCKET_ERROR)
            cerr<< "failed to send message, error: " 
                << GetLastError() 
                << endl;

        else 
            cout << "message sent" << endl;

        this_thread::sleep_for(std::chrono::seconds(1));
    }
    closesocket(sc);
    WSACleanup();

    return system("pause");
}