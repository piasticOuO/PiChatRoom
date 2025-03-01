//
// Created by piasticouo on 25-2-19.
//

#ifndef CHATSYS_H
#define CHATSYS_H
#include <unordered_map>

#include "Database.h"
#include "../../tools/include/Message.hpp"
#include "../../tools/include/ThreadPool.hpp"

class Network;

class ChatSys {
    std::shared_ptr<Database> db;
    Network &network;
    ThreadPool &pool;
    std::unordered_map<int, int> chat_users;
public:
    ChatSys(std::shared_ptr<Database> db, Network &network, ThreadPool &pool);
    ~ChatSys();
    void Broadcast(const Json &msg);
    int AddUser(int userid, int userfd);
    int RemoveUser(int userid);
};

#endif //CHATSYS_H
