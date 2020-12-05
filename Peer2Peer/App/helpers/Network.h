//
// Created by gabe on 2020-12-05.
//

#ifndef PEER2PEER_NETWORK_H
#define PEER2PEER_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define INDEX_PORT 8123
#define INDEX_ADDR "0.0.0.0"
#define DOWNLOAD_PORT 8124


struct sock_t {
    int sockfd;
    int port;
    char * addr;
    struct sockaddr_in sockaddr;
    socklen_t sockaddr_len;
};

struct sock_t init_tcp_client(int port, char * host){

    struct sock_t sock;
    struct hostent * hostp;

    bzero((char *)&sock.sockaddr, sizeof(sock.sockaddr));
    sock.addr = (char *)malloc(20);

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

struct sock_t init_server_tcp(int port, int listen_size){

    struct sock_t sock;

    if((sock.sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("Error 01: failed to create sock \n");
        sock.sockfd = -1;
        return sock;
    }

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_addr.s_addr = INADDR_ANY;
    sock.sockaddr.sin_port = htons(port);

    if (setsockopt(sock.sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        printf("Error 06: failed to reuse addr");

    if (setsockopt(sock.sockfd, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
        printf("Error 07: failed to reuse port");

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

struct sock_t init_client_udp(int port, char * host){
    struct sock_t sock;
    struct timeval tv;
    tv.tv_sec = 1;

    bzero((char *)&sock.sockaddr, sizeof(sock.sockaddr));

    sock.sockaddr_len = sizeof(sock.sockaddr);

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_port = htons(port);
    inet_aton(host, &sock.sockaddr.sin_addr);

    sock.sockfd = socket(AF_INET, SOCK_DGRAM, 0);

//    if(setsockopt(sock.sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
//        printf("Error 08: could not set timeout");

    connect(sock.sockfd, (struct sockaddr *)&sock.sockaddr, sock.sockaddr_len);

    return sock;
}

struct sock_t init_server_udp(int port){
    struct sock_t sock;

    bzero((char *)&sock.sockaddr, sizeof(sock.sockaddr));

    sock.sockaddr_len = sizeof(sock.sockaddr);

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sockaddr.sin_port = htons(port);

    sock.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sock.sockfd, (struct sockaddr *)&sock.sockaddr, sock.sockaddr_len);

    return sock;

}

#endif //PEER2PEER_NETWORK_H
