//
// Created by piasticouo on 25-2-15.
//

#ifndef LOGINSYS_H
#define LOGINSYS_H
#include <memory>
#include <queue>

#include "Database.h"
#include "Network.h"
#include "../../tools/include/ThreadPool.h"

class LoginSys {
    Database &db;
    Network &network;
    ThreadPool &pool;
public:
    LoginSys(Database &db, Network &network, ThreadPool &pool);
    ~LoginSys();
    void Login(int id, const std::string &password);
    void Reg(const std::string &password, const std::string &name);
};

#endif //LOGINSYS_H
