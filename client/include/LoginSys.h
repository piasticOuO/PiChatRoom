//
// Created by piasticouo on 25-2-20.
//

#ifndef LOGINSYS_H
#define LOGINSYS_H

#include "../../tools/include/ThreadPool.hpp"
#include "../../tools/include/Message.hpp"
#include "Network.h"

class LoginSys {
    int login_status{};
    int login_id{};
    Network &network;
    ThreadPool &pool;
public:
    LoginSys(Network &network, ThreadPool &pool);
    ~LoginSys();
    int login(int id, const std::string &password);
    int reg(const std::string &name, const std::string &password);
    void handleLoginRet(const Json &ret);
    void handleRegRet(const Json &ret);
    int getLoginStatus();
    int getLoginID();
    void setLoginStatus(int login_status);
};

#endif //LOGINSYS_H
