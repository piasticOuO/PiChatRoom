//
// Created by piasticouo on 25-2-28.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

#include "json.hpp"
using Json = nlohmann::json;

enum MessageType {
  LOGIN, LOGINRET, REG, REGRET, CHAT, CHATRET, CHATMSG
};

void divideMessage(const std::string &s, std::function<void(Json)> callback);

#endif //MESSAGE_H
