//
// Created by piasticouo on 25-2-15.
//

#include "../include/LoginSys.h"
#include "../include/Network.h"
#include "../include/ChatSys.h"

LoginSys::LoginSys(std::shared_ptr<Database> db, Network &network, ThreadPool &pool, ChatSys &chat_sys) : db(db), network(network), pool(pool), chat_sys(chat_sys) {
    db -> ExecuteUpdate("CREATE TABLE IF NOT EXISTS users("
             "id INT AUTO_INCREMENT PRIMARY KEY,"
             "username VARCHAR(50) NOT NULL UNIQUE,"
             "password VARCHAR(50) NOT NULL"
             ");");
}

LoginSys::~LoginSys() = default;

void LoginSys::Reg(const Json &json) {

    Json ret{
            {"type", REGRET},
            {"result", "ERROR"},
            {"id", -1}
    };

    std::cout << "[DEBUG] LoginSys: Registeration" << std::endl;

    std::string name = json["name"], password = json["password"];
    std::string query = "INSERT INTO users(username, password) VALUES('" + name + "', '" + password + "');";
    int id = -1;
    int result = db -> ExecuteUpdate(query, &id);

    std::cout << "[DEBUG] LoginSys: Registeration completed" << std::endl;

    if (result == 1) {
        chat_sys.AddUser(id, json["fd"]);
        ret["result"] = "OK";
        ret["id"] = id;
    }

    network.SendMessage(json["fd"], ret);
}

void LoginSys::Login(const Json &json) {

    Json ret{
            {"type", LOGINRET},
            {"result", "ERROR"}
    };

    int id = json["id"], fd = json["fd"];
    std::string password = json["password"];
    std::string query = "SELECT password FROM users WHERE id = '" + std::to_string(id) + "';";
    auto [stmt_ptr, result_ptr] = db -> ExecuteQuery(query);
    while (result_ptr -> next()) {
        if (result_ptr -> getString("password") == password) {
            chat_sys.AddUser(id, fd);
            ret["result"] = "OK";
            network.SendMessage(fd, ret);
            return;
        }
    }
    network.SendMessage(json["fd"], ret);
}

void LoginSys::Logout(int id) {
    chat_sys.RemoveUser(id);
}