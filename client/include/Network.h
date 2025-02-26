//
// Created by piasticouo on 25-2-20.
//

#ifndef NETWORK_H
#define NETWORK_H
#include "LoginSys.h"
#include "ChatSys.h"
#include "../../tools/include/ThreadPool.h"
#include "../../tools/include/json.hpp"
using Json = nlohmann::json;

class Network {
    int sockfd;
    ThreadPool &pool;
    LoginSys *login_sys;
    ChatSys *chat_sys;

public:
    Network(int port, ThreadPool &pool);
    ~Network();
    void initDependency(LoginSys &login_sys, ChatSys &chat_sys);
    void listening();
    void handleMessage(const Json &msg);
    void sendMessage(const Json &msg);
};

#endif //NETWORK_H
