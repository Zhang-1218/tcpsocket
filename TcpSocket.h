#pragma once

#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>


class TcpSocket
{
public:
    TcpSocket();
    ~TcpSocket();
    bool Socket();
    bool Bind(const std::string& ip, const u_int16_t port);
    bool Listen(const int queuelen = 10);
    bool Connect(const std::string& ip, const u_int16_t port);
    bool Accpet(int* cfd, std::string* ip, u_int16_t* port);
    bool Recv(const int cfd, std::string* buf);
    bool Send(const int cdf, std::string& buf);
    bool Close();
    int getSockfd();

private:
    int _sockfd;
};

