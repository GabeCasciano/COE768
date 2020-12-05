cmake_minimum_required(VERSION 3.17)
project(App)

execute_process(COMMAND cmake-build-debug/delete.sh)
add_executable(App main.c common.h )
add_executable(File_test tests/file_test.c common.h)
add_executable(Content_test tests/content_test.c common.h) 