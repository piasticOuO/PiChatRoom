//
// Created by piasticouo on 25-2-20.
//

#ifndef NETWORK_H
#define NETWORK_H
#include "../../server/include/SafeQueue.h"

class Network {
    int sockfd;
    SafeQueue<std::string> msg_queue;
public:
    Network(int port, SafeQueue<std::string> &msg_queue);
    ~Network();
    void listening();
};

#endif //NETWORK_H
