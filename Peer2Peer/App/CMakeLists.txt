cmake_minimum_required(VERSION 3.17)
project(App)

add_compile_options(-fno-stack-protector)


execute_process(COMMAND cmake-build-debug/delete.sh)
add_executable(App main.c common.h)
add_executable(File_test tests/file_test.c common.h)
add_executable(Content_test tests/content_test.c common.h)
add_executable(PDU_test tests/pdu_test.c common.h)
add_executable(TCP_test tests/tcp_test.c common.h)
add_executable(UDP_test tests/udp_test.c common.h)
add_executable(FORK_test tests/fork_test.c common.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(App PRIVATE Threads::Threads)