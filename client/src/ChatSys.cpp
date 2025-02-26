//
// Created by piasticouo on 25-2-25.
//

#include "../include/ChatSys.h"

ChatSys::ChatSys(Network &network, ThreadPool &pool) : network(network), pool(pool) {

}

ChatSys::~ChatSys() {

}

void ChatSys::sendMessage(const std::string &str) {
    Json json{
        {"type", "chat"},
        {"content", str}
    };
    pool.enqueue(std::bind(network.sendMessage, json));
}

void ChatSys::handleChatRet(const Json &ret) {

}

void ChatSys::getMessage(const Json &ret) {

}

