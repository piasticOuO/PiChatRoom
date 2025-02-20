//
// Created by piasticouo on 25-2-15.
//

#ifndef LOGINSYS_H
#define LOGINSYS_H
#include <memory>
#include <queue>

#include "Database.h"
#include "Message.h"
#include "SafeQueue.h"

class LoginSys {
    Database &db;
    SafeQueue<Message> &login_queue, &reg_queue;
    SafeQueue<Message> &loginret_queue, &regret_queue;
public:
    LoginSys(Database &db, SafeQueue<Message> &login_queue, SafeQueue<Message> &reg_queue, SafeQueue<Message> &loginret_queue, SafeQueue<Message> &regret_queue);
    ~LoginSys();
    int Login(const std::string &id, const std::string &password);
    int Reg(const std::string &password, const std::string &username);
    void LoginListener();
    void RegListener();
};

#endif //LOGINSYS_H
