cmake_minimum_required(VERSION 3.30)
project(PiChatRoom)

set(CMAKE_CXX_STANDARD 20)

add_executable(PiChatRoomServer server/src/Server.cpp
        server/src/Network.cpp
        server/include/Network.h
        server/src/Database.cpp
        server/include/Database.h
        server/src/LoginSys.cpp
        server/include/LoginSys.h
        server/src/ChatSys.cpp
        server/include/ChatSys.h

        tools/src/ThreadPool.cpp

        tools/include/ThreadPool.h
)

add_executable(PiChatRoomClient client/src/Client.cpp
        client/src/LoginSys.cpp
        client/src/Network.cpp

        client/include/LoginSys.h
        client/include/Network.h
        client/src/ChatSys.cpp
        client/include/ChatSys.h


        tools/src/ThreadPool.cpp

        tools/include/ThreadPool.h
)