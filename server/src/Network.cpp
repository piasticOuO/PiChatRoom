//
// Created by piasticouo on 25-2-11.
//

#include "../include/Network.h"
#include "../include/ChatSys.h"
#include "../include/LoginSys.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/epoll.h>

struct Message;

Network::Network(int port, ThreadPool &pool):
                port(port), pool(pool) {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id == -1) {
        perror("Could not create socket");
    }
    int opt = 1;
    if (setsockopt(socket_id, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt error");
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

void Network::injectDependency(LoginSys &login_sys, ChatSys &chat_sys) {
    this -> login_sys = &login_sys;
    this -> chat_sys = &chat_sys;
}

[[noreturn]] void Network::listenConnect() {
    while (!stop_flag) {
        sockaddr_in client{};
        socklen_t len = sizeof(client);
        int client_id = accept(socket_id, (sockaddr *) &client, &len);
        if (client_id == -1) {
            perror("Could not accept");
            continue;
        }
        epoll_event temp_epoll_event{};
        temp_epoll_event.events = EPOLLIN;
        temp_epoll_event.data.fd = client_id;
        epoll_ctl(epoll_id, EPOLL_CTL_ADD, client_id, &temp_epoll_event);
        std::cout << "[Info] Connection from fd : " + std::to_string(client_id) + " Accepted" << std::endl;
    }
}

[[noreturn]] void Network::listenMessage() {
    std::unique_ptr<epoll_event[]> events = std::make_unique<epoll_event[]>(1024);
    while (!stop_flag) {
        int events_cnt = epoll_wait(epoll_id, events.get(), 1024, -1);
        for (int i = 0; i < events_cnt; i++) {
            int fd = events[i].data.fd;
            std::cout << "[Info] Heard from fd " << fd << std::endl;
            handleClient(fd);
        }
    }
}

void Network::closeConnect(int fd) {
    epoll_ctl(epoll_id, EPOLL_CTL_DEL, fd, nullptr);
}

void Network::handleMessage(int fd, Json json) {
    if (json.is_object()) {
        json["fd"] = fd;
        MessageType type = json["type"];
        switch (type) {
            case LOGIN:
                std::cout << "[Info] Heard from " << fd << " : Login Request" << std::endl;
                pool.enqueue(std::bind(&LoginSys::Login, login_sys, json));
            break;
            case REG:
                std::cout << "[Info] Heard from " << fd << " : Reg Request" << std::endl;
                pool.enqueue(std::bind(&LoginSys::Reg, login_sys, json));
            break;
            case CHAT:
                std::cout << "[Info] Heard from " << fd << " : Chat" << std::endl;
                pool.enqueue(std::bind(&ChatSys::Broadcast, chat_sys, json));
            break;
            default:
                std::cerr << "Unknown JSON type" << std::endl;
        }
    } else {
        std::cerr << "Could not parse JSON" << std::endl;
    }
}



void Network::handleClient(int fd) {
    std::unique_ptr<char> buf(new char[BUFSIZ]);
    ssize_t len = read(fd, buf.get(), 1);
    if (len > 0) {
        std::string str(1, buf.get()[0]);
        while (len > 0) {
            len = read(fd, buf.get(), BUFSIZ);
            str += std::string(buf.get(), len);
        }
        divideMessage(str, [this, fd](const Json& json) {
            pool.enqueue([this, fd, json]() {
                this->handleMessage(fd, json);
            });
        });
    } else if (len == 0) {
        closeConnect(fd);
    }
}

void Network::sendMessage(int fd, const Json &msg) {
    std::string msgstr = msg.dump();
    int len = msgstr.size();
    msgstr = "O" + std::to_string(len) + "X" + msgstr;
    std::cout << "Sending Message： " << msgstr << std::endl;
    send(fd, msgstr.c_str(), msgstr.size(), MSG_NOSIGNAL);
}
