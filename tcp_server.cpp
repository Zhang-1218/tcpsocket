#include <iostream>
#include "TcpSocket.h"

#define CHECK_RET(p) if((p)==false){return false;}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Arguments error, please input : ./tcp_server ip port" << std::endl;
        return -1;
    }

    std::string ip = argv[1];
    u_int16_t port = std::stoi(argv[2]);
    int cfd;

    TcpSocket tcpsock;
    CHECK_RET(tcpsock.Socket());
    CHECK_RET(tcpsock.Bind(ip, port));
    CHECK_RET(tcpsock.Listen());

    std::string clnt_ip;
    u_int16_t clnt_port;
    std::string buf;
    CHECK_RET(tcpsock.Accpet(&cfd, &clnt_ip, &clnt_port));
    
    while(1)
    {
        CHECK_RET(tcpsock.Recv(cfd, &buf));
        std::cout << "Client [" << clnt_ip << ":" << clnt_port << "] send messages: " << buf << std::endl;
        buf.clear();
        std::cout << "Server send : ";
        std::cin >> buf;
        CHECK_RET(tcpsock.Send(cfd, buf));
        buf.clear();
    }
    tcpsock.Close();
    close(cfd);

    return 0;
}

