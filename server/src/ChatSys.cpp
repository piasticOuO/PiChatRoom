//
// Created by piasticouo on 25-2-19.
//

#include "../include/ChatSys.h"

#include <iostream>

ChatSys::ChatSys(Database &db, Network &network, ThreadPool &pool) : db(db), network(network), pool(pool) {}

ChatSys::~ChatSys() = default;

int ChatSys::AddUser(int userfd, int userid) {
    chat_users.emplace(userfd, userid);
    return 0;
}

int ChatSys::RemoveUser(int userfd) {
    auto it = chat_users.find(userfd);
    if (it == chat_users.end()) {
        return -1;
    }
    chat_users.erase(it);
    return 0;
}

void ChatSys::Broadcast(const Json &msg) {
    int sender = msg["id"];
    std::string str;
    db.query("SELECT username FROM users WHERE id = " + std::to_string(sender) + ";");
    db.commit();
    MYSQL_RES* res = db.getResult();
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        str = row[0];
    }
    if (str.empty()) {
        std::cerr << "Invaild userid" << std::endl;
    }
    Json msgall;
    msgall["sender"] = str;
    msgall["content"] = msg["content"];
    for (auto [fd, id] : chat_users) {
        network.SendMessage(fd, msgall);
    }
}


