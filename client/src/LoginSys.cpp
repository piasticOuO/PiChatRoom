#include "../include/LoginSys.h"
#include "../../tools/include/json.hpp"
using Json = nlohmann::json;

#include <cmath>
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
        setLoginStatus(1);
    } else {
        setLoginStatus(-1);
    }
}

void LoginSys::handleRegRet(const Json &ret) {
    if (ret["result"] == "OK") {
        setLoginStatus(1);
        login_id = ret["id"];
    } else {
        setLoginStatus(-1);
    }
}

int LoginSys::getLoginID() {
    return login_id;
}

int LoginSys::login(int id, const std::string &password) {
    Json json{
        {"type", "login"},
        {"id", id},
        {"password", password}
    };
    pool.enqueue(std::bind(network.sendMessage, json));
    setLoginStatus(0);
    return 0;
}

int LoginSys::reg(const std::string &name, const std::string &password) {
    Json json{
            {"type", "reg"},
            {"name", name},
            {"password", password}
    };
    pool.enqueue(std::bind(network.sendMessage, json));
    setLoginStatus(0);
    return 0;
}

