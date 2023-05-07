//
// Created by Emad on 5/6/2023.
//

#ifndef CMAKE_CLIENT_H
#define CMAKE_CLIENT_H

#ifdef _WIN32
#include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
#include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
#include <Windows.h>
#else
#include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h> // for sleep()
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define MSGBUFSIZE 256

class client {

private:
    char* m_group{"239.255.255.250"}; // e.g. 239.255.255.250 for SSDP
    int m_port{0};
    const char *m_message{""};
    int fd{0};
    char msgbuf[MSGBUFSIZE];
    struct sockaddr_in addr;
public:
    client(char* group , const int &port);
    virtual ~client();
    void message(std::string str);
    void set_file_descriptor_linux();
    void setup();
    void send();
    void receive();


public:

};


#endif //CMAKE_CLIENT_H
