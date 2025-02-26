//
// Created by piasticouo on 25-2-25.
//

#ifndef CHATSYS_H
#define CHATSYS_H
#include "Network.h"
#include "../../tools/include/json.hpp"
using Json = nlohmann::json;

class ChatSys {
    Network &network;
    ThreadPool &pool;
    public:
    ChatSys(Network &network, ThreadPool &pool);
    ~ChatSys();
    void sendMessage(const std::string &str);
    void handleChatRet(const Json &ret);
    void getMessage(const Json &ret);
};

#endif //CHATSYS_H
