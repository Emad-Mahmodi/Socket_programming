//Implement by Emad Mahmodi

#include "UDPSocket.h"

#ifdef WIN32
typedef int socklen_t;
#endif

UDPSocket::UDPSocket(int port, char* address, bool broadcast, bool reusesock)
{
#ifdef WIN32
    retval = WSAStartup(MAKEWORD(2,2),&wsaData);
#endif

    sockaddr_in addr;
    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    //set up bind address
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    //set up address to use for sending
    memset(&outaddr,0,sizeof(outaddr));
    outaddr.sin_family = AF_INET;
    outaddr.sin_addr.s_addr = inet_addr(address);
    outaddr.sin_port = htons(port);

#ifdef WIN32
    bool bOptVal = 1;
    int bOptLen = sizeof(bool);
#else
    int OptVal = 1;
#endif

    if (broadcast)
#ifdef WIN32
        retval = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&bOptVal, bOptLen);
#else
        retval = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &OptVal, sizeof(OptVal));
#endif

    if (reusesock)
#ifdef WIN32
        retval = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);
#else
        retval = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &OptVal, sizeof(OptVal));
#endif

    retval = bind(sock,(struct sockaddr *)&addr,sizeof(addr));
}

UDPSocket::~UDPSocket()
{
#if WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}

int UDPSocket::getAddress(const char * name, char * addr)
{
    struct hostent *hp;
    if ((hp = gethostbyname(name)) == NULL) return (0);
    strcpy(addr, inet_ntoa( *( struct in_addr*)( hp->h_addr)));
    return (1);
}

const char* UDPSocket::getAddress(const char * name)
{
    struct hostent *hp;
    if ((hp = gethostbyname(name)) == NULL) return (0);
    strcpy(ip, inet_ntoa( *( struct in_addr*)( hp->h_addr)));
    return ip;
}

long UDPSocket::receive(char* msg, int msgsize)
{
    struct sockaddr_in sender;
    socklen_t sendersize = sizeof(sender);
    int retval = recvfrom(sock,msg,msgsize,0, (struct sockaddr *)&sender, &sendersize);
    strcpy(received,inet_ntoa(sender.sin_addr));
    return retval;
}

char* UDPSocket::received_from()
{
    return received;
}

long UDPSocket::send(const char* msg, int msgsize)
{
    return sendto(sock, msg, msgsize, 0, (struct sockaddr *)&outaddr,sizeof(outaddr));
}

long UDPSocket::sendTo(const char* msg, int msgsize, const char* addr)
{
    outaddr.sin_addr.s_addr = inet_addr(addr);
    return sendto(sock, msg, msgsize, 0, (struct sockaddr *)&outaddr,sizeof(outaddr));
}

//void UDPSocket::bind() {
//    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
//        perror("bind");
//        return 1;
//    }
//}
