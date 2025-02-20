//
// Created by piasticouo on 25-2-15.
//

#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

struct Message {
    time_t timestamp;
    std::string str;
    int sender;
    int receiver;
};

#endif //MESSAGE_H
