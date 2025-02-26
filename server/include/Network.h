//
// Created by piasticouo on 25-2-11.
//

#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>

#include "Message.h"
#include "SafeQueue.h"

class Network {
private:
    int socket_id;
    int port;
    sockaddr_in address{};
    int epoll_id;
    SafeQueue<Message> &login_queue, &reg_queue, &chat_queue;
    SafeQueue<Message> &loginret_queue, &regret_queue, &chatret_queue;
    int stop_flag{};
public:
    Network(int port, SafeQueue<Message> &login_queue, SafeQueue<Message> &reg_queue, SafeQueue<Message> &chat_queue, SafeQueue<Message> &loginret_queue, SafeQueue<Message> &regret_queue, SafeQueue<Message> &chatret_queue);
    ~Network();
    [[noreturn]] void ListenConnect();
    [[noreturn]] void ListenMessage();
    int HandleClient(int fd);
    void ConnectReturner();
    int SendMessage(int fd, const std::string &msg);
};


#endif //NETWORK_H
