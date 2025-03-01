//
// Created by piasticouo on 25-2-11.
//

#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>

#include "../../tools/include/ThreadPool.hpp"
#include "../../tools/include/Message.hpp"

class LoginSys;
class ChatSys;

class Network {
    int socket_id;
    int port;
    sockaddr_in address{};
    int epoll_id;
    LoginSys *login_sys;
    ChatSys *chat_sys;
    ThreadPool &pool;
    int stop_flag{};
public:
    Network(int port, ThreadPool &pool);
    ~Network();
    void InjectDependency(LoginSys &login_sys, ChatSys &chat_sys);
    [[noreturn]] void ListenConnect();
    [[noreturn]] void ListenMessage();
    void closeConnect(int fd);
    void HandleClient(int fd);
    static void SendMessage(int fd, const Json &msg);
};


#endif //NETWORK_H
