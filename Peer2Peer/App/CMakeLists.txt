project(App)

add_executable(App main.c common.h network.h file_manipulation.h download_client.c content_server.c index_server.c)
add_executable(Tests test.c common.h file_manipulation.h)