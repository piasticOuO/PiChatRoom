//
// Created by piasticouo on 25-2-20.
//

#ifndef LOGINSYS_H
#define LOGINSYS_H
#include <string>

#include "../../server/include/SafeQueue.h"

class LoginSys {
    int fd;
public:
    LoginSys(int fd);
    ~LoginSys();
    int login(const std::string &id, const std::string &password);
    int reg(const std::string &name, const std::string &password);

};

#endif //LOGINSYS_H
