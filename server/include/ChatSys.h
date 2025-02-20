//
// Created by piasticouo on 25-2-19.
//

#ifndef CHATSYS_H
#define CHATSYS_H
#include <set>
#include <unordered_map>

#include "Database.h"
#include "Message.h"
#include "SafeQueue.h"

class ChatSys {
    Database &db;
    SafeQueue<Message> &chat_queue, &chatret_queue;
    std::unordered_map<int, int> chat_users;
    public:
    ChatSys(Database &db, SafeQueue<Message> &chat_queue, SafeQueue<Message> &chatret_queue);
    ~ChatSys();
    void ChatListener();
    int Broadcast(Message msg);
    int AddUser(int userid, int userfd);
    int RemoveUser(int userid);
};

#endif //CHATSYS_H
