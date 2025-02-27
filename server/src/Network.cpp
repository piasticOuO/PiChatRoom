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

Network::Network(int port, ThreadPool &pool):
                port(port), pool(pool) {
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

void Network::InjectDependency(LoginSys &login_sys, ChatSys &chat_sys) {
    this -> login_sys = &login_sys;
    this -> chat_sys = &chat_sys;
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
            HandleClient(fd);
        }
    }
}

void Network::closeConnect(int fd) {
    epoll_ctl(epoll_id, EPOLL_CTL_DEL, fd, nullptr);
}


void Network::HandleClient(int fd) {
    char buf[BUFSIZ];
    ssize_t len = recv(fd, buf, BUFSIZ, 0);
    if (len == 0) {
        closeConnect(fd);
        return;
    }
    Json json = Json::parse(std::string(buf, len));
    if (json.is_object()) {
        json["fd"] = fd;
        switch (json["type"]) {
            case "login":
                login_sys -> Login(json["id"], json["password"]);
                break;
            case "ret":
                login_sys -> Reg(json["password"], json["name"]);
                break;
            case "chat":
                chat_sys -> Broadcast(json["content"]);
                break;
            default:
                std::cerr << "Unknown JSON type" << std::endl;
        }
    } else {
        std::cerr << "Could not parse JSON" << std::endl;
    }
}

void Network::SendMessage(int fd, const Json &msg) {
    send(fd, msg.dump().c_str(), 0, MSG_NOSIGNAL);
}