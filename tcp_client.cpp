#include <iostream>
#include "TcpSocket.h"

#define CHECK_RET(p) if((p)==false){return false;}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Arguments error, please input : ./tcp_client ip port" << std::endl;
        return -1;
    }

    std::string ip = argv[1];
    u_int16_t port = std::stoi(argv[2]);
    
    TcpSocket tcpsock;
    CHECK_RET(tcpsock.Socket());
    CHECK_RET(tcpsock.Connect(ip, port));

    int cfd = tcpsock.getSockfd();
    std::string buf;
    while(1)
    {
        std::cout << "Client send: ";
        std::cin >> buf;
        CHECK_RET(tcpsock.Send(cfd, buf));
        buf.clear();

        CHECK_RET(tcpsock.Recv(cfd, &buf));
        std::cout << "Server [" << ip << ":" << port << "] send messages:" << buf << std::endl;
        buf.clear();
    }

    tcpsock.Close();
    close(cfd);

    return 0;
}

