cmake_minimum_required(VERSION 3.15)
project(L4_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Server server.c)
add_executable(Client client.c)
add_executable(Test test.c)