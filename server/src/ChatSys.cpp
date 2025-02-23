//
// Created by piasticouo on 25-2-19.
//

#include "../include/ChatSys.h"

ChatSys::ChatSys(Database &db, SafeQueue<Message> &chat_queue, SafeQueue<Message> &chatret_queue) :
                db(db), chat_queue(chat_queue), chatret_queue(chatret_queue) {}

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

int ChatSys::Broadcast(Message msg) {
    int sender = chat_users[msg.sender];
    std::string str;
    db.query("SELECT username FROM users WHERE id = " + std::to_string(sender) + ";");
    db.commit();
    MYSQL_RES* res = db.getResult();
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        str = row[0];
    }
    if (str.empty()) {
        return 3;
    }
    msg.str = "C " + str + ":" + msg.str;
    for (auto [fd, id] : chat_users) {
        Message newmsg = msg;
        newmsg.receiver = fd;
        chatret_queue.push(newmsg);
    }
    return 0;
}

[[noreturn]] void ChatSys::ChatListener() {
    while (true) {
        if (!chat_queue.empty()) {
            Message msg = chat_queue.pop();
            Broadcast(msg);
        }
    }
}


