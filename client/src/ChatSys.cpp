//
// Created by piasticouo on 25-2-25.
//

#include "../include/ChatSys.h"
#include <iostream>

ChatSys::ChatSys(Network &network, ThreadPool &pool) : network(network), pool(pool) {}

ChatSys::~ChatSys() = default;

void ChatSys::sendMessage(const std::string &str) {
    Json json{
        {"type", CHAT},
        {"sender", chatid},
        {"content", str}
    };
    pool.enqueue(std::bind(&Network::sendMessage, &network, json));
}

void ChatSys::handleChatRet(const Json &ret) {
    if (ret["result"] != "OK") {
        std::cerr << "Your message fail sending." << std::endl;
    }
}

void ChatSys::getMessage(const Json &ret) {
    std::cout << ret["sender"] << ": " << ret["content"] << std::endl;
}

void ChatSys::setChatID(int id) {
    chatid = id;
}

