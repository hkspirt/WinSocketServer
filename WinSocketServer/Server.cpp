#include <iostream>
#include <winsock2.h>

using namespace std;

#define SERVPORT    5050
#define SERVIP      "127.0.0.1"
#pragma comment(lib,"ws2_32.lib")

int main(void)
{
    do 
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        SOCKADDR_IN addrServer;
        memset(&addrServer, 0, sizeof(SOCKADDR_IN));
        addrServer.sin_family = AF_INET;
        addrServer.sin_port = htons(SERVPORT);
        addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)) == SOCKET_ERROR)
        {
            cout<<"bind failed!"<<endl;
            break;
        }

        listen(sockServer, 5);

        SOCKET               sockClient;        // 连接socket
        SOCKADDR_IN          addrClient;        // 客户端地址信息
        int                  addrLength = sizeof(addrClient);
        while(1)
        {
            sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &addrLength);
            if (sockClient == INVALID_SOCKET)
            {
                cout<<"accept failed"<<endl;
            }
            else
            {
                cout<<"accept client:"<<inet_ntoa(addrClient.sin_addr)<<","<<ntohs(addrClient.sin_port)<<endl;      
                if (send(sockClient, "connect success", 16, 0) == SOCKET_ERROR)
                {
                    cout<<"send failed!"<<endl;
                }
            }
            closesocket(sockClient);
        }

        closesocket(sockServer);
        WSACleanup();

        return 0;
    } while (0);
    getchar();
    return -1;
}