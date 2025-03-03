//
// Created by piasticouo on 25-2-20.
//

#include "../include/Network.h"
#include "../include/ChatSys.h"
#include "../include/LoginSys.h"

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

void Network::injectDependency(LoginSys &login_sys, ChatSys &chat_sys) {
    this -> login_sys = &login_sys;
    this -> chat_sys = &chat_sys;
}

void Network::listening() {
    while (true) {
        std::unique_ptr<char> buf(new char[BUFSIZ]);
        ssize_t len = read(sockfd, buf.get(), 1);
        if (len > 0) {
            std::string str(1, buf.get()[0]);
            while (len > 0) {
                len = read(sockfd, buf.get(), BUFSIZ);
                str += std::string(buf.get(), len);
            }
            divideMessage(str, [this](const Json& json) {
                pool.enqueue([this, json]() {
                    this->handleMessage(json);
                });
            });
        } else if (len == 0) {
            std::cout << "[INFO] Server closed" << std::endl;
            break; // 退出循环
        }
    }
}



void Network::handleMessage(const Json &msg) {
    MessageType type = msg["type"];
    switch (type) {
        case LOGINRET :
            login_sys -> handleLoginRet(msg);
            break;
        case REGRET :
            login_sys -> handleRegRet(msg);
            break;
        case CHATRET :
            chat_sys -> handleChatRet(msg);
            break;
        case CHATMSG :
            chat_sys -> getMessage(msg);
            break;
        default :
            std::cerr << "Unknown json type" << std::endl;
    }
}

void Network::sendMessage(const Json &msg) {
    std::string msgstr = msg.dump();
    int len = msgstr.size();
    msgstr = "O" + std::to_string(len) + "X" + msgstr;
    std::cout << "Sending Message： " << msgstr << std::endl;
    send(sockfd, msgstr.c_str(), msgstr.size(), MSG_NOSIGNAL);
}
