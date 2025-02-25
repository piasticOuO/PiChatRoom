//
// Created by piasticouo on 25-2-20.
//

#ifndef LOGINSYS_H
#define LOGINSYS_H

#include "../include/Message.h"
#include "../include/SafeQueue.h"

class LoginSys {
    SafeQueue<Message> &msg_queue;
    int login_status{};
public:
    LoginSys(SafeQueue<Message> &msg_queue);
    ~LoginSys();
    int login(const std::string &id, const std::string &password);
    int reg(const std::string &name, const std::string &password);
    int getLoginStatus();
    void setLoginStatus(int login_status);
};

#endif //LOGINSYS_H
