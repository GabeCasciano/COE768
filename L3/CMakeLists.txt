cmake_minimum_required(VERSION 3.15)
project(L3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Server server.c)
add_executable(Client client.c)
add_executable(Server_threaded most_of_c_server/server.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Server PRIVATE Threads::Threads)
target_link_libraries(Client PRIVATE Threads::Threads)
