//
// Created by piasticouo on 25-2-15.
//

#include "../include/LoginSys.h"
LoginSys::LoginSys(Database &db, Network &network, ThreadPool &pool) : db(db), network(network), pool(pool) {
    db.query("CREATE TABLE IF NOT EXISTS users("
             "id INT AUTO_INCREMENT PRIMARY_KEY,"
             "username VARCHAR(50) NOT NULL UNIQUE,"
             "password VARCHAR(50) NOT NULL"
             ");");
    db.commit();
}

LoginSys::~LoginSys() = default;

void LoginSys::Reg(const std::string &password, const std::string &name) {
    std::string query = "INSERT INTO users(name, password) VALUES('" + name + "', '" + password + "');";
    db.query(query);
    db.commit();
}

void LoginSys::Login(int id, const std::string& password) {
    std::string query = "SELECT password FROM users WHERE id = '" + std::to_string(id) + "';";
    db.query(query);
    MYSQL_RES *res = db.getResult();
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] == password) {

        }
    }
}