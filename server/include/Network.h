//
// Created by piasticouo on 25-2-11.
//

#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>

#include "../../tools/include/ThreadPool.h"
#include "../include/ChatSys.h"
#include "../include/LoginSys.h"

class Network {
    int socket_id;
    int port;
    sockaddr_in address{};
    int epoll_id;
    LoginSys *login_sys;
    ChatSys *chat_sys;
    ThreadPool &pool;
    int stop_flag{};
public:
    Network(int port, ThreadPool &pool);
    ~Network();
    void InjectDependency(LoginSys &login_sys, ChatSys &chat_sys);
    [[noreturn]] void ListenConnect();
    [[noreturn]] void ListenMessage();
    void closeConnect(int fd);
    void HandleClient(int fd);
    void SendMessage(int fd, const Json &msg);
};


#endif //NETWORK_H
