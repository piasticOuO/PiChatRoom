//
// Created by piasticouo on 25-2-11.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

class Database {

    using StmtPtr = std::unique_ptr<sql::Statement>;
    using ResultPtr = std::unique_ptr<sql::ResultSet>;
    using ConnPtr = std::unique_ptr<sql::Connection>;

    sql::Driver *driver;
    ConnPtr conn;
    int port;

    public:
    Database(int port, const std::string &host, const std::string &user, const std::string &password, const std::string &db);
    ~Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    int ExecuteUpdate(const std::string &sql, int *insert_id = nullptr);
    std::pair<StmtPtr, ResultPtr> ExecuteQuery(const std::string &sql);

};

#endif //DATABASE_H
