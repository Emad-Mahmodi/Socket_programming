//
// Created by Emad on 5/6/2023.
//

#include "client.h"

client::client(char* group , const int &port): m_group{group},m_port{port} {

#ifdef _WIN32
    //
    // Initialize Windows Socket API with given VERSION.
    //
    WSADATA wsaData;
    if (WSAStartup(0x0101, &wsaData)) {
        perror("WSAStartup");
        return;
    }
    fd = WSAStartup(MAKEWORD(2,2), &wsaData);
#else
    set_file_descriptor();
#endif
    setup();
}

client::~client() {
    WSACleanup();
}

void client::message(std::string str) {
    m_message = str.c_str();
}

void client::set_file_descriptor_linux() {
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return;
    }
}

void client::setup() {
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(m_group);
    addr.sin_port = htons(m_port);
}

void client::send() {
    int addrlen = sizeof(addr);
    recvfrom(
            fd,
            msgbuf,
            MSGBUFSIZE,
            0,
            (struct sockaddr *) &addr,
            &addrlen
    );
}
