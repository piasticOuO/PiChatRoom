//
// Created by piasticouo on 25-2-11.
//

#include "../include/Database.h"

#include <iostream>
#include <ostream>

Database::Database(int port, const std::string &host, const std::string &user, const std::string &password, const std::string &db) :
                  port (port), host (host), user (user), password (password), db (db) {
    mysql = mysql_init(nullptr);
    if (mysql == nullptr) {
        std::cerr << "mysql_init failed" << std::endl;
    }
    connect();
}

Database::~Database() {
    mysql_close(mysql);
}

bool Database::connect() {
    if (mysql_real_connect(mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), 0, nullptr, 0) == nullptr) {
        std::cerr << "mysql_real_connect failed" << std::endl;
        return false;
    }
    return true;
}

int Database::query(const std::string &query) {
    return mysql_query(mysql, query.c_str());
}

MYSQL_RES *Database::getResult() {
    return mysql_store_result(mysql);
}

bool Database::commit() {
    return mysql_commit(mysql);
}