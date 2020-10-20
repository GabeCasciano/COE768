cmake_minimum_required(VERSION 3.17)
project(L5 C)

set(CMAKE_C_STANDARD 11)

add_executable(Server main.c)
add_executable(Client cli.c)