//
// Created by piasticouo on 25-2-20.
//

#include "../include/Network.h"

#include <iostream>
#include <ostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

Network::Network(int port, ThreadPool &pool) : pool(pool), login_sys(), chat_sys() {
    int ret = 0;
    ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        std::cerr << "Socket creation failed." << std::endl;
    }
    sockfd = ret;

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr.s_addr);

    ret = connect(sockfd, (sockaddr *) &sin, sizeof(sin));
    if (ret == -1) {
        std::cerr << "Connection with the server failed." << std::endl;
    }
}

Network::~Network() {
    close(sockfd);
}

void Network::initDependency(LoginSys &login_sys, ChatSys &chat_sys) {
    this -> login_sys = &login_sys;
    this -> chat_sys = &chat_sys;
}


void Network::listening() {
    char buf[BUFSIZ];
    while (true) {
        ssize_t len = recv(sockfd,buf,0,MSG_WAITALL);
        std::string str = std::string(buf,len);
        Json msg = Json::parse(str);
        pool.enqueue(std::bind(this -> handleMessage, msg));
    }
}

void Network::handleMessage(const Json &msg) {
    switch (msg["type"]) {
        case "loginret" :
            login_sys -> handleLoginRet(msg);
            break;
        case "regret" :
            login_sys -> handleRegRet(msg);
            break;
        case "chatret" :
            chat_sys -> handleChatRet(msg);
            break;
        case "chatmsg" :
            chat_sys -> getMessage(msg);
            break;
        default :
            std::cerr << "Unknown json type" << std::endl;
    }
}

void Network::sendMessage(const Json &msg) {
    send(sockfd, msg.dump().c_str(), 0, MSG_NOSIGNAL);
}
