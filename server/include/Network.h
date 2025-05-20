//
// Created by piasticouo on 25-2-11.
//

#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>

#include "../../tools/include/ThreadPool.hpp"
#include "../../tools/include/Message.hpp"

class LoginSys;
class ChatSys;

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
    void injectDependency(LoginSys &login_sys, ChatSys &chat_sys);
    void listenConnect();
    void listenMessage();
    void closeConnect(int fd);
    void handleClient(int fd);
    void handleMessage(int fd, Json json);
    void sendMessage(int fd, const Json &msg);
};


#endif //NETWORK_H
