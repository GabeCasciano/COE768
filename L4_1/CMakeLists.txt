cmake_minimum_required(VERSION 3.15)
project(L4_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Server server.c headers.h networking.h)
add_executable(Client client.c headers.h networking.h)