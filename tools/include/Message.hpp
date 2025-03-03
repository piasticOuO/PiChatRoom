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

void divideMessage(const std::string &s, std::function<void(Json)> callback) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'O') {
            int j = i + 1, len = 0;
            while (isdigit(s[j])) {
                len = len * 10 + s[j] - '0';
                j ++;
            }
            if (s[j] == 'X') {
                Json json = Json::parse(s.substr(j + 1, len));
                callback(json);
            }
            i = j + 1 + len;
        } else {
            std::cerr << "[WARN] Incorrect message head" << std::endl;
        }
    }
}

#endif //MESSAGE_H
