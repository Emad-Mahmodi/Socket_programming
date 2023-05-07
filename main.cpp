#include <iostream>
#include "UDPSocket.h"
#include <thread>
#include <string>
int main() {
    UDPSocket *s = new UDPSocket(5000, "255.255.255.255", TRUE, TRUE);

    std::string msg = "";
    std::cout << "Enter your message" << std::endl;

    while (1)  {
        std::cin>>msg;
        s->send(msg.c_str(), msg.length());
    }
    return 0;
}
