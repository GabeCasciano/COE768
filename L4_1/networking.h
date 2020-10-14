//
// Created by gabriel on 2020-10-13.
//

#ifndef L4_1_NETWORKING_H
#define L4_1_NETWORKING_H

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>


int init_client(int * sock, struct sockaddr_in * server_addr, int server_port, struct hostent * hostp, char * host){
    if((*sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // Prepare the sock
        printf("Error 01: could not create sock \n");
        return -1;
    }

    // Prepare the addr structure
    bzero((char *) server_addr, sizeof(struct sockaddr_in));
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(server_port);

    if(hostp = gethostbyname(host)){ //Collect the host address
        memcpy(hostp->h_addr, (char *) &server_addr->sin_addr, hostp->h_length);
    }
    else if(inet_aton(host, (struct in_addr *) &server_addr->sin_addr)){
        printf("Error 02: Can not locate servers address \n");
        return -2;
    }

    if(connect(*sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){ // Connect to server_addr
        printf("Error 03: Could not connect to server_addr \n");
    }
    return 0;
}

int init_server(int * sock, struct sockaddr_in * addr, int port, int size){
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("Error 01: failed to create sock \n");
        return -1;
    }

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);

    if(bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
        printf("Error 04: could not bind server \n");
        return -4;
    }

    if(listen(sock, size) < 0){
        printf("Error 05: Failed to listed to port \n");
        return -5;
    }

    return 0;
}

struct connection{
    int sock;
    struct sockaddr_in addr;
};

int accept_new_conns(int * server_sock, struct connection * client){
    client->sock = accept(server_sock, (struct sockaddr *)&client->addr,(socklen_t *) sizeof(client->addr));
    if(client->sock < 0){
        printf("Error 06: Could not accept new connection \n");
        return -6;
    }

    return 0;
}

#endif //L4_1_NETWORKING_H
