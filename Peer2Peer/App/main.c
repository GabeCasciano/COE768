//
// Created by gabe on 2020-11-28.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_PORT 8123
#define SERVER_ADDR "0.0.0.0"

#define CLIENT_PORT 8124

#define MAX_DATA_SIZE


int main(int argc, char ** argv) {
    int application_type = 0;
    int running = 1;

    if (argc > 1) {
        if (strcmp(argv[1], CMD_SERVER) == 0) {
            application_type = 1;
        } else if (strcmp(argv[1], CMD_CLIENT) == 0) {
            application_type = 2;
        }
    }

    if(application_type == 1){
        // server application



    }
    else if(application_type == 2){
        // client application



    }


    return 0;

}