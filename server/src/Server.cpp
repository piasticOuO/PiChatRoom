//
// Created by piasticouo on 25-2-11.
//

#include <queue>
#include <thread>

#include "../include/ChatSys.h"
#include "../include/Network.h"
#include "../include/Database.h"
#include "../include/LoginSys.h"
#include "../../tools/include/ThreadPool.hpp"

int main() {

    auto database = std::make_shared<Database>(8080, "localhost", "piasticOuO", "ubuntu", "ChatRoom");
    ThreadPool pool(24);

    Network network(9527, pool);
    ChatSys chat_sys(database, network, pool);
    LoginSys login_sys(database, network, pool, chat_sys);
    network.InjectDependency(login_sys, chat_sys);

    std::cout << "[Info] Server started." << std::endl;


    std::thread connectlistener_thread(&Network::ListenConnect, &network);
    std::thread messagelistener_thread(&Network::ListenMessage, &network);

    connectlistener_thread.join();
    messagelistener_thread.join();

    std::cout << "Bye!" << std::endl;

    return 0;
}
