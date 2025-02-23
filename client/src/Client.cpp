
#include <iostream>
#include <ostream>

#include "../../server/include/SafeQueue.h"
#include "../include/LoginSys.h"
#include "../include/Network.h"

int main() {

    SafeQueue<std::string> msg_queue;

    LoginSys login_sys(&msg_queue);
    Network network(9527, &msg_queue);

    std::cout << "Hello World! Welcome to the piChatRoom!" << std::endl;
    while (true) {
        std::cout << "Please tell me what do you want to do (L/R): ";
        std::string str;
        std::cin >> str;
        if (str == "L" || str == "l") {
            std::string id, password;
            std::cout << "id: ";
            std::cin >> id;
            std::cout << "password: ";
            std::cin >> password;
            if (login_sys.login(id, password)) {
                break;
            }
        } else if (str == "R" || str == "r") {
            std::string name, password;
            std::cout << "name: ";
            std::cin >> name;
            std::cout << "password: ";
            std::cin >> password;
            login_sys.reg(name, password);
        } else {
            std::cout << "Invaild input! Try Again." << std::endl;
        }
    }



    return 0;
}
