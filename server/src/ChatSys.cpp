//
// Created by piasticouo on 25-2-19.
//

#include "../include/LoginSys.h"
#include "../include/Network.h"
#include "../include/ChatSys.h"


#include <iostream>

ChatSys::ChatSys(std::shared_ptr<Database> db, Network &network, ThreadPool &pool) : db(db), network(network), pool(pool) {}

ChatSys::~ChatSys() = default;

int ChatSys::AddUser(int userid, int userfd) {
    chat_users.emplace(userid, userfd);
    return 0;
}

int ChatSys::RemoveUser(int userid) {
    auto it = chat_users.find(userid);
    if (it == chat_users.end()) {
        return -1;
    }
    chat_users.erase(it);
    return 0;
}

void ChatSys::Broadcast(const Json &msg) {

    Json msgret{
            {"type", CHATRET},
            {"result", "OK"}
    };

    int sender = msg["sender"];
    std::string sender_name;
    std::string query = "SELECT username FROM users WHERE id = " + std::to_string(sender) + ";";
    auto [stmt_ptr, result_ptr] = db -> ExecuteQuery(query);
    while (result_ptr -> next()) {
        sender_name = result_ptr -> getString("username");
    }
    if (sender_name.empty()) {
        std::cerr << "Invaild userid" << std::endl;
    }
    Json msgall{
        {"type", CHATMSG},
        {"sender", sender_name},
        {"content", msg["content"]}
    };
    for (auto [id, fd] : chat_users) {
        network.SendMessage(fd, msgall);
    }
    network.SendMessage(msg["fd"], msgret);
}


