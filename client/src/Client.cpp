
#include <iostream>
#include <ostream>

#include "../include/ChatSys.h"
#include "../include/LoginSys.h"
#include "../include/Network.h"

int main() {
    ThreadPool pool(4);
    Network network(9527, pool);
    LoginSys login_sys(network, pool);
    ChatSys chat_sys(network, pool);
    network.initDependency(login_sys, chat_sys);

    std::cout << "Hello World! Welcome to the piChatRoom!" << std::endl;
    // Login
    int id = -1;
    while (true) {
        std::cout << "Please tell me what do you want to do (L/R): ";
        std::string str;
        std::cin >> str;
        if (str == "L" || str == "l") {
            std::string password;
            std::cout << "id: ";
            std::cin >> id;
            std::cout << "password: ";
            std::cin >> password;
            login_sys.login(id, password);
            while (!login_sys.getLoginStatus()) {}
            if (login_sys.getLoginStatus() == 1) { break; }
        } else if (str == "R" || str == "r") {
            std::string name, password;
            std::cout << "name: ";
            std::cin >> name;
            std::cout << "password: ";
            std::cin >> password;
            login_sys.reg(name, password);
            while (!login_sys.getLoginStatus()) {}
            if (login_sys.getLoginStatus() == 1) { break; }

        } else {
            std::cout << "Invaild input! Try Again." << std::endl;
        }
    }

    // Chat
    std::cout << "Successfully login! Welcome to the chatroom." << std::endl;
    while (true) {
        std::string str;
        getline(std::cin, str);
        chat_sys.sendMessage(str);
    }

    return 0;
}
