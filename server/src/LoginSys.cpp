//
// Created by piasticouo on 25-2-15.
//

#include "../include/LoginSys.h"
LoginSys::LoginSys(Database &db, SafeQueue<Message> &login_queue, SafeQueue<Message> &reg_queue, SafeQueue<Message> &loginret_queue, SafeQueue<Message> &regret_queue):
                   db(db), login_queue(login_queue), reg_queue(reg_queue), loginret_queue(loginret_queue), regret_queue(regret_queue) {
    db.query("CREATE TABLE IF NOT EXISTS users("
             "id INT AUTO_INCREMENT PRIMARY_KEY,"
             "username VARCHAR(50) NOT NULL UNIQUE,"
             "password VARCHAR(50) NOT NULL"
             ");");
    db.commit();
}

LoginSys::~LoginSys() = default;

int LoginSys::Reg(const std::string &password, const std::string &username) {
    std::string query = "INSERT INTO users(name, password) VALUES('" + username + "', '" + password + "');";
    db.query(query);
    db.commit();
    return 1;
}

int LoginSys::Login(const std::string& id, const std::string& password) {
    std::string query = "SELECT password FROM users WHERE id = " + id + ";";
    db.query(query);
    MYSQL_RES *res = db.getResult();
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] == password) {
            return 1;
        }
    }
    return 0;
}

[[noreturn]] void LoginSys::LoginListener() {
    while (true) {
        Message msg = login_queue.pop();
        std::string id, password;
        id = msg.str.substr(0, msg.str.find(' '));
        password = msg.str.substr(msg.str.find(' ') + 1, msg.str.length() - msg.str.find(' ') - 1);
        int ret = Login(id, password);
        Message retmsg;
        retmsg.str = "L " + std::to_string(ret);
        retmsg.receiver = msg.sender;
        retmsg.sender = 0;
        retmsg.timestamp = time(nullptr);
        loginret_queue.push(retmsg);
    }
}

void LoginSys::RegListener() {
    while (true) {
        Message msg = reg_queue.pop();
        std::string username, password;
        username = msg.str.substr(0, msg.str.find(' '));
        password = msg.str.substr(msg.str.find(' ') + 1, msg.str.length() - msg.str.find(' ') - 1);
        int ret = Reg(username, password);
        Message retmsg;
        retmsg.str = "R " + std::to_string(ret);
        retmsg.receiver = msg.sender;
        retmsg.sender = 0;
        retmsg.timestamp = time(nullptr);
        regret_queue.push(retmsg);
    }
}