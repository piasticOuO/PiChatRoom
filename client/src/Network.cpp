//
// Created by piasticouo on 25-2-20.
//

#include "../include/Network.h"

#include <iostream>
#include <ostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

Network::Network(int port, SafeQueue<std::string> &msg_queue) {
    int ret = 0;
    ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        std::cerr << "Socket creation failed." << std::endl;
    }
    sockfd = ret;

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_pton(AF_INET,"127.0.0.1",&sin.sin_addr.s_addr);

    ret = connect(sockfd, (sockaddr *)&sin, sizeof(sin));
    if (ret == -1) {
        std::cerr << "Connection with the server failed." << std::endl;
    }
}

Network::~Network() {
    close(sockfd);
}

void Network::listening() {
    char buf[BUFSIZ];
    while (true) {
        ssize_t len = recv(sockfd,buf,0,MSG_WAITALL);
        std::string str = buf;
        if (str[0] == 'L') {

        } else if (str[0] == 'R') {

        } else if (str[0] == 'C') {

        }
    }
}
