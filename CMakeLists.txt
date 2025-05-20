cmake_minimum_required(VERSION 3.22)
project(PiChatRoom)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(PiChatRoomServer server/src/Server.cpp
        server/src/Network.cpp
        server/src/Database.cpp
        server/src/LoginSys.cpp
        server/src/ChatSys.cpp

        tools/include/ThreadPool.hpp
        tools/include/Message.hpp

        tools/src/ThreadPool.cpp
        tools/src/Message.cpp
)

target_link_libraries(PiChatRoomServer PRIVATE
        mysqlcppconn
        mysqlclient
        Threads::Threads
)

target_include_directories(PiChatRoomServer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/server/include
        /usr/include/mysql-cppconn/jdbc
)

add_executable(PiChatRoomClient client/src/Client.cpp
        client/src/LoginSys.cpp
        client/src/Network.cpp
        client/src/ChatSys.cpp

        client/include/LoginSys.h
        client/include/Network.h
        client/include/ChatSys.h

        tools/include/ThreadPool.hpp
        tools/include/Message.hpp

        tools/src/ThreadPool.cpp
        tools/src/Message.cpp
)

target_link_libraries(PiChatRoomClient PRIVATE
        Threads::Threads
)
