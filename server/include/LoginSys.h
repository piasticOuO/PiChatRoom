//
// Created by piasticouo on 25-2-15.
//

#ifndef LOGINSYS_H
#define LOGINSYS_H

#include "Database.h"
#include "../../tools/include/ThreadPool.hpp"
#include "../../tools/include/Message.hpp"

class ChatSys;
class Network;

class LoginSys {
    std::shared_ptr<Database> db;
    ChatSys &chat_sys;
    Network &network;
    ThreadPool &pool;
public:
    LoginSys(std::shared_ptr<Database> db, Network &network, ThreadPool &pool, ChatSys &chat_sys);
    ~LoginSys();
    void Login(const Json &json);
    void Reg(const Json &json);
    void Logout(int id);
};

#endif //LOGINSYS_H
