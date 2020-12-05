//
// Created by gabe on 2020-11-28.
//

#ifndef PEER2PEER_NETWORK_H
#define PEER2PEER_NETWORK_H

#include "common.h"

#define INDEX_PORT 8123
#define INDEX_ADDR "0.0.0.0"
#define LISTENERS 2

// --- Network functions

struct sock_t {
    int is_tcp;
    int sockfd;
    int port;
    char * addr;
    struct sockaddr_in sockaddr;
    socklen_t sockaddr_len;
};

struct sock_t init_server_tcp(int port, int listen_size){

    struct sock_t sock;
    sock.is_tcp = 1;

    if((sock.sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("Error 01: failed to create sock \n");
        sock.sockfd = -1;
        return sock;
    }

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_addr.s_addr = INADDR_ANY;
    sock.sockaddr.sin_port = htons(port);

    if(bind(sock.sockfd, (struct sockaddr *)&sock.sockaddr, sizeof(sock.sockaddr)) < 0){
        printf("Error 04: could not bind server \n");
        sock.sockfd = -4;
        return sock;
    }

    if(listen(sock.sockfd, listen_size) < 0){
        printf("Error 05: Failed to listed to port \n");
        sock.sockfd = -5;
        return sock;
    }

    sock.port = port;
    return sock;

}

struct sock_t init_tcp_client(int port, char * host){

    struct sock_t sock;
    struct hostent * hostp;

    bzero((char *)&sock.sockaddr, sizeof(sock.sockaddr));
    sock.is_tcp = 1;

    if((sock.sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("Error 01: could not create socket \n");
        sock.sockfd = -1;
        return sock;
    }

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_port = htons(port);

    if((hostp = gethostbyname(host)))
        bcopy(hostp->h_addr_list[0], (char *) &sock.sockaddr.sin_addr, hostp->h_length);
    else if(inet_aton(host, (struct in_addr *) &sock.sockaddr.sin_addr)) {
        printf("Error 2: couldn not resolve host id \n");
        sock.sockfd = -2;
        return sock;
    }

    if(connect(sock.sockfd, (struct sockaddr * ) &sock.sockaddr, sizeof(sock.sockaddr)) == -1) {
        printf("Error 3: could not connect to server \n");
        sock.sockfd = -3;
        return sock;
    }
    sock.port = port;
    sock.addr = (char *)malloc(sizeof(host));
    strcpy(sock.addr, host);

    return sock;
}

struct sock_t init_server_udp(int port){
    struct sock_t sock;

    bzero((char *)&sock.sockaddr, sizeof(sock.sockaddr));
    sock.is_tcp = 0;

    sock.sockaddr_len = sizeof(sock.sockaddr);

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sockaddr.sin_port = htons(port);

    sock.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sock.sockfd, (struct sockaddr *)&sock.sockaddr, sock.sockaddr_len);

    return sock;

}

struct sock_t init_client_udp(int port, char * host){
    struct sock_t sock;

    bzero((char *)&sock.sockaddr, sizeof(sock.sockaddr));
    sock.is_tcp = 0;

    sock.sockaddr_len = sizeof(sock.sockaddr);

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_port = htons(port);
    inet_aton(host, &sock.sockaddr.sin_addr);

    sock.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    connect(sock.sockfd, (struct sockaddr *)&sock.sockaddr, sock.sockaddr_len);

    return sock;
}

#endif //PEER2PEER_NETWORK_H
