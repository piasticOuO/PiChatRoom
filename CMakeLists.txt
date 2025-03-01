cmake_minimum_required(VERSION 3.30)
project(PiChatRoom)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(PiChatRoomServer server/src/Server.cpp
        server/src/Network.cpp
        server/src/Database.cpp
        server/src/LoginSys.cpp
        server/src/ChatSys.cpp

        server/include/LoginSys.h
        server/include/ChatSys.h
        server/include/Network.h
        server/include/Database.h

        tools/include/ThreadPool.hpp
        tools/src/ThreadPool.cpp
)

target_link_libraries(PiChatRoomServer PRIVATE
        mysqlcppconn
        mysqlclient
        Threads::Threads
)

add_executable(PiChatRoomClient client/src/Client.cpp
        client/src/LoginSys.cpp
        client/src/Network.cpp
        client/src/ChatSys.cpp

        client/include/LoginSys.h
        client/include/Network.h
        client/include/ChatSys.h

        tools/include/ThreadPool.hpp
        tools/src/ThreadPool.cpp
)

target_link_libraries(PiChatRoomClient PRIVATE
        Threads::Threads
)
