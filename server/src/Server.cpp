//
// Created by piasticouo on 25-2-11.
//

#include <queue>
#include <thread>

#include "../include/ChatSys.h"
#include "../include/Network.h"
#include "../include/Database.h"
#include "../include/LoginSys.h"
#include "../include/SafeQueue.h"
#include "../include/Message.h"

int main() {

    Database database(8080, "piasticOuO", "piasticOuO", "ubuntu", "ChatRoom");
    SafeQueue<Message> login_queue, chat_queue, reg_queue;
    SafeQueue<Message> loginret_queue, regret_queue, chatret_queue;

    Network network(9527, login_queue,  reg_queue, chat_queue, loginret_queue, regret_queue, chatret_queue);
    std::thread connectlistener_thread(network.ListenConnect, NULL);
    std::thread messagelistener_thread(network.ListenMessage, NULL);
    std::thread messageSender_thread(network.ConnectReturner, NULL);

    LoginSys login_sys(database, login_queue, chat_queue, regret_queue, chatret_queue);
    ChatSys chat_sys(database, chat_queue, chatret_queue);

    std::thread loginlistener_thread(login_sys.LoginListener, NULL);
    std::thread reglistener_thread(login_sys.RegListener, NULL);
    std::thread chatlistener_thread(chat_sys.ChatListener, NULL);;

    return 0;
}
