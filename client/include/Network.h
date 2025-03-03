//
// Created by piasticouo on 25-2-20.
//

#ifndef NETWORK_H
#define NETWORK_H
#include "../../tools/include/ThreadPool.hpp"
#include "../../tools/include/Message.hpp"

class LoginSys;
class ChatSys;

class Network {
    int sockfd;
    ThreadPool &pool;
    LoginSys *login_sys;
    ChatSys *chat_sys;

public:
    Network(int port, ThreadPool &pool);
    ~Network();
    void injectDependency(LoginSys &login_sys, ChatSys &chat_sys);
    void listening();
    void handleMessage(const Json &msg);
    void sendMessage(const Json &msg);
};

#endif //NETWORK_H
