#include "../include/LoginSys.h"

#include <cmath>
#include <iostream>
#include <unistd.h>

LoginSys::LoginSys(Network &network, ThreadPool &pool) :  network(network), pool(pool) {}

LoginSys::~LoginSys() = default;

int LoginSys::getLoginStatus() {
    return login_status;
}

void LoginSys::setLoginStatus(int login_status) {
    this -> login_status = login_status;
}

void LoginSys::handleLoginRet(const Json &ret) {
    if (ret["result"] == "OK") {
        std::cout << "Successfully login! Welcome to the chatroom." << std::endl;
        setLoginStatus(1);
    } else {
        std::cout << "Your Login Request is rejected. Try Again?" << std::endl;
        setLoginStatus(-1);
    }
}

void LoginSys::handleRegRet(const Json &ret) {
    if (ret["result"] == "OK") {
        std::cout << "Successfully register! Welcome to the chatroom." << std::endl;
        std::cout << "Your ID is " << ret["id"] << " , please remember it!" << std::endl;
        setLoginStatus(1);
        login_id = ret["id"];
    } else {
        std::cout << "Your Register Request is rejected. Try Again?" << std::endl;
        setLoginStatus(-1);
    }
}

int LoginSys::getLoginID() {
    return login_id;
}

int LoginSys::login(int id, const std::string &password) {
    Json json{
        {"type", LOGIN},
        {"id", id},
        {"password", password}
    };
    pool.enqueue(std::bind(&Network::sendMessage, &network,json));
    std::cout << "Your Login Request is posting..." << std::endl;
    setLoginStatus(0);
    return 0;
}

int LoginSys::reg(const std::string &name, const std::string &password) {
    Json json{
            {"type", REG},
            {"name", name},
            {"password", password}
    };
    pool.enqueue(std::bind(&Network::sendMessage, &network,json));
    std::cout << "Your Register Request is posting..." << std::endl;
    setLoginStatus(0);
    return 0;
}

