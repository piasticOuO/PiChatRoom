#include "../include/LoginSys.h"

#include <cmath>
#include <unistd.h>

LoginSys::LoginSys(SafeQueue<Message> &msg_queue) : msg_queue(msg_queue) {}

LoginSys::~LoginSys() = default;

int LoginSys::getLoginStatus() {
    return login_status;
}

void LoginSys::setLoginStatus(int login_status) {
    this -> login_status = login_status;
}

int LoginSys::login(const std::string &id, const std::string &password) {
    Message msg;
    msg.str = "L " + id + " " + password;
    msg.timestamp = time(nullptr);
    msg.messageType = Message::LOGIN;
    msg_queue.push(msg);
    setLoginStatus(0);
    return 0;
}

int LoginSys::reg(const std::string &name, const std::string &password) {
    Message msg;
    msg.str = "L " + name + " " + password;
    msg.timestamp = time(nullptr);
    msg.messageType = Message::REG;
    msg_queue.push(msg);
    return 0;
}

