//
// Created by piasticouo on 25-2-11.
//

#include "../include/Database.h"

#include <iostream>
#include <ostream>
#include <mysql_driver.h>

Database::Database(int port, const std::string &host, const std::string &user, const std::string &password, const std::string &db) :
                  port (port) {
    driver = sql::mysql::get_driver_instance();
    conn.reset(driver -> connect(host.c_str(), user.c_str(), password.c_str()));
    conn -> setSchema(db);
    std::cout << "[DEBUG] Database port: " << port << std::endl;  // 打印端口值
}

Database::~Database(){
    if (conn) {
        conn -> close();
    }
}

int Database::ExecuteUpdate(const std::string& sql, int *insert_id) {

    if (!conn || conn->isClosed()) {
        std::cerr << "[ERROR] Database closed!" << std::endl;
    }

    try {
        sql::Statement* stmt = conn->createStatement();
        int count = stmt->executeUpdate(sql);
        if (insert_id != nullptr) {
            stmt->execute("SELECT LAST_INSERT_ID()");
            sql::ResultSet* res = stmt->getResultSet();
            res->next();
            *insert_id = res->getUInt64(1);
        }
        delete stmt;
        return count;
    } catch (sql::SQLException &e) {
        if (e.getErrorCode() == 1062) {
            return 0;
        }
        throw std::runtime_error("SQL Error: " + std::string(e.what()));
    }
}

using StmtPtr = std::unique_ptr<sql::Statement>;
using ResultPtr = std::unique_ptr<sql::ResultSet>;
std::pair<StmtPtr, ResultPtr> Database::ExecuteQuery(const std::string& sql) {
    try {
        StmtPtr stmt_ptr(conn->createStatement());
        ResultPtr res_ptr(stmt_ptr->executeQuery(sql));
        return std::pair(std::move(stmt_ptr), std::move(res_ptr));
    } catch (sql::SQLException &e) {
        throw std::runtime_error("SQL Error: " + std::string(e.what()));
    }
}