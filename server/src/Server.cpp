//
// Created by piasticouo on 25-2-11.
//

#include <queue>
#include <thread>

#include "../include/ChatSys.h"
#include "../include/Network.h"
#include "../include/Database.h"
#include "../include/LoginSys.h"
#include "../../tools/include/ThreadPool.h"

int main() {

    Database database(8080, "piasticOuO", "piasticOuO", "ubuntu", "ChatRoom");
    ThreadPool pool(24);

    Network network(9527, pool);
    LoginSys login_sys(database, network, pool);
    ChatSys chat_sys(database, network, pool);

    std::thread connectlistener_thread(network.ListenConnect, NULL);
    std::thread messagelistener_thread(network.ListenMessage, NULL);

    connectlistener_thread.join();
    messagelistener_thread.join();

    return 0;
}
