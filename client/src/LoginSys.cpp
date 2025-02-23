#include "../include/LoginSys.h"

#include <unistd.h>

LoginSys::LoginSys(int fd) : fd(fd) {

}

LoginSys::~LoginSys() {
    close(fd);
}


int LoginSys::login(const std::string &id, const std::string &password) {

    return 0;
}

int LoginSys::reg(const std::string &name, const std::string &password) {
    int id = -1;
    return id;
}

