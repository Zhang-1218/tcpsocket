#include "TcpSocket.h"

TcpSocket::TcpSocket()
    :_sockfd(-1)
{}

TcpSocket::~TcpSocket()
{
    if(_sockfd > 0){
        _sockfd = -1;
    }
}

bool TcpSocket::Socket()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(_sockfd < 0)
    {
        perror("socket error");
        return false;
    }

    return true;
}

bool TcpSocket::Bind(const std::string &ip, const u_int16_t port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(addr);
    int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0)
    {
        perror("bind error");
        return false;
    }

    return true;
}

bool TcpSocket::Listen(int queuelen)
{
   int ret = listen(_sockfd, queuelen);
   if(ret < 0)
   {
       perror("listen error");
       return false;
   }

   return true;
}

bool TcpSocket::Connect(const std::string &ip, const u_int16_t port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(addr);
    int ret = connect(_sockfd, (struct sockaddr*)&addr, len);
    if(ret < 0)
    {
        perror("connect error");
        return false;
    }

    return true;
}

bool TcpSocket::Accpet(int *cfd, std::string *ip = nullptr, u_int16_t *port = nullptr)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t len = sizeof(addr);
again:
    *cfd = accept(_sockfd, (struct sockaddr*)&addr, &len);
    if(*cfd < 0)
    {
        if((errno == ECONNABORTED) || (errno == EINTR))
            goto again;
        else
        {
            perror("accpet error");
            return false;
        }
    }
    
    if(ip != nullptr)
    {
        *ip = inet_ntoa(addr.sin_addr);
    }
    if(port != nullptr)
    {
        *port = ntohs(addr.sin_port);
    }

    return true;
}

bool TcpSocket::Recv(const int cfd, std::string *buf)
{
    char tmp[1024] = {0};
    int ret = recv(cfd, tmp, 1024, 0);
    if(ret < 0)
    {
        perror("read errror");
        return false;
    }else if(ret == 0)
    {
        std::cout << "connect shutdown" << std::endl;
        return false;
    }
    buf->assign(tmp, ret);
    
    return true;
}

bool TcpSocket::Send(const int cdf, const std::string &buf)
{
    int total_len = 0;
    while(total_len < (int)buf.size())
    {
        int ret = send(cdf, buf.c_str() + total_len, buf.size() - total_len, 0);
        if(ret < 0)
        {
            perror("write error");
            return false;
        }
        total_len += ret;
    }

    return true;
}

int TcpSocket::getSockfd()
{
    return _sockfd;
}

