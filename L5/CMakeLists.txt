cmake_minimum_required(VERSION 3.17)
project(L5 C)

set(CMAKE_C_STANDARD 11)


add_executable(Server server.c common.h)
add_executable(Server_old playing_around/server_1.c)
add_executable(Client client.c common.h)
add_executable(Client_old playing_around/client_1.c)
add_executable(Test playing_around/test.c common.h)

set_target_properties(Client PROPERTIES LINK_FLAGS -W --stack 1048576)