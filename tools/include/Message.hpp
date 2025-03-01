//
// Created by piasticouo on 25-2-28.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include "json.hpp"
using Json = nlohmann::json;

enum MessageType {
  LOGIN, LOGINRET, REG, REGRET, CHAT, CHATRET, CHATMSG
};

#endif //MESSAGE_H
