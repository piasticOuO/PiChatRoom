//
// Created by piasticouo on 25-2-20.
//

#ifndef NETWORK_H
#define NETWORK_H
#include "../include/Message.h"
#include "../include/SafeQueue.h"

class Network {
    int sockfd;
    SafeQueue<Message> &msg_queue;
public:
    Network(int port, SafeQueue<Message> &msg_queue);
    ~Network();
    void listening();
};

#endif //NETWORK_H
