//
// Created by piasticouo on 25-2-11.
//

#include "../include/Network.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <unistd.h>
#include <sys/epoll.h>

struct Message;

Network::Network(int port, SafeQueue<Message> &login_queue, SafeQueue<Message> &reg_queue, SafeQueue<Message> &chat_queue, SafeQueue<Message> &loginret_queue, SafeQueue<Message> &regret_queue, SafeQueue<Message> &chatret_queue):
                port(port), login_queue(login_queue), reg_queue(reg_queue), chat_queue(chat_queue), loginret_queue(loginret_queue), regret_queue(regret_queue), chatret_queue(chatret_queue) {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id == -1) {
        perror("Could not create socket");
    }
    if (bind(socket_id, (sockaddr *) &address, sizeof(address)) == -1) {
        perror("Could not bind");
    }
    if (listen(socket_id, SOMAXCONN) == -1) {
        perror("Could not listen");
    }
    epoll_id = epoll_create(1024);
}

Network::~Network() {
    close(socket_id);
    stop_flag = 1;
}

[[noreturn]] void Network::ListenConnect() {
    while (!stop_flag) {
        sockaddr_in client{};
        socklen_t len = sizeof(client);
        int socket_id = accept(socket_id, (sockaddr *) &client, &len);
        if (socket_id == -1) {
            perror("Could not accept");
            continue;
        }
        epoll_event temp_epoll_event{};
        temp_epoll_event.events = EPOLLIN;
        temp_epoll_event.data.fd = socket_id;
        epoll_ctl(epoll_id, EPOLL_CTL_ADD, socket_id, &temp_epoll_event);
    }
}

[[noreturn]] void Network::ListenMessage() {
    std::unique_ptr<epoll_event[]> events = std::make_unique<epoll_event[]>(1024);
    while (!stop_flag) {
        int events_cnt = epoll_wait(epoll_id, events.get(), 1024, -1);
        for (int i = 0; i < events_cnt; i++) {
            int fd = events[i].data.fd;
            int ret = HandleClient(fd);
            if (ret == 0) {
                epoll_ctl(epoll_id, EPOLL_CTL_DEL, fd, nullptr);
            }
        }
    }
}

int Network::HandleClient(int fd) {

    char buf[BUFSIZ];
    int len = recv(fd, buf, 1, 0);
    if (len == 0) {
        return 0;
    }
    char source = buf[0];
    Message msg;
    while (true) {
        len = recv(fd, buf, BUFSIZ, 0);
        if (len == 0) {
            break;
        }
        msg.str = std::to_string(fd) + " ";
        msg.str += buf;
        msg.receiver = 0;
        msg.sender = fd;
        msg.timestamp = time(nullptr);
        switch (source) {
            case 'L':
                login_queue.push(msg);
                break;
            case 'C':
                chat_queue.push(msg);
                break;
            case 'R':
                reg_queue.push(msg);
                break;
            default:
                std::cerr << "Invaild source: " << source << std::endl;
        }
    }
    return 1;
}

[[noreturn]] void Network::ConnectReturner() {
    while (!stop_flag) {
        if (!regret_queue.empty()) {
            Message msg = regret_queue.pop();
            SendMessage(msg.receiver, msg.str);
        }
        if (!loginret_queue.empty()) {
            Message msg = loginret_queue.pop();
            SendMessage(msg.receiver, msg.str);
        }
        if (!chatret_queue.empty()) {
            Message msg = chatret_queue.pop();
            SendMessage(msg.receiver, msg.str);
        }
    }
}


int Network::SendMessage(int fd, const std::string &msg) {
    write(fd, msg.c_str(), msg.size());
    return 0;
}