//
// Created by piasticouo on 25-2-11.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <mysql/mysql.h>

class Database {
    MYSQL *mysql;
    int port;
    std::string host;
    std::string user;
    std::string password;
    std::string db;

    public:
    Database(int port, const std::string &host, const std::string &user, const std::string &password, const std::string &db);
    ~Database();
    bool connect();
    int query(const std::string &query);
    MYSQL_RES *getResult();
    bool commit();
};

#endif //DATABASE_H
