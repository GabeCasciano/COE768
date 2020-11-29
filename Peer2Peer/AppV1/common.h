//
// Created by gabe on 2020-11-18.
//

#ifndef PEER2PEER_COMMON_H
#define PEER2PEER_COMMON_H

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


#define PDU_DATA_LENGTH_DEFAULT 100

#define PDU_ACK 'A'
#define PDU_ERROR 'E'
#define PDU_REGISTER 'R'
#define PDU_REQUEST 'D'
#define PDU_SEARCH 'S'
#define PDU_DEREGISTER 'T'
#define PDU_CONTENT 'C'
#define PDU_LIST 'O'

// --- PDU datatypes & functions

struct pdu_t {
    char type;
    char * data;
};

struct packet_t {
    int length;
    struct pdu_t * pdus;
};

struct pdu_t init_pdu(const char type, char * data){
    int data_length = PDU_DATA_LENGTH_DEFAULT;
    struct pdu_t pdu;

    pdu.type = type;

    if(type != PDU_ACK){
        pdu.data = (char *)malloc(data_length);
        strcpy(pdu.data, data);
    }

    return pdu;
}

char * serialized(struct pdu_t pdu, char * dest){
    sprintf(dest, "%c", pdu.type);
    strcat(dest, ",");
    strcat(dest, pdu.data);

    return dest;
}

struct pdu_t unserialized(char * cereal, struct pdu_t * pdu){

    pdu->type = cereal[0];
    bzero(pdu->data, strlen(cereal));
    strncpy(pdu->data, cereal+2, strlen(cereal));

    return *pdu;
}

struct packet_t init_packet(int packet_data_size, char * data, int data_length){
    struct packet_t packet;
    packet.length = ceil(data_length/packet_data_size);
    packet.pdus = (struct pdu_t *)malloc(packet.length);

    int data_cursor = 0;

    for(int i = 0; i < packet.length; i++) {
        packet.pdus[i].type = PDU_CONTENT;
        packet.pdus[i].data = (char *) malloc(packet_data_size);
        strncpy(packet.pdus[i].data, data + data_cursor, packet_data_size);
        data_cursor += packet_data_size;
    }

    return packet;
}


// --- Network functions

struct sock_t {
    int is_tcp;
    int sockfd;
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

// --- File functions

int filesize(char * filename){
    char _filename[strlen(filename)];
    char cwd[256];
    struct stat st;

    bzero(&_filename, strlen(filename));
    bzero(&cwd, 256);

    strcpy(&_filename, filename);
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/tmp/");
    strcat(cwd, _filename);

    if(stat(cwd, &st) != -1)
        return st.st_blksize;
    return -1;

}


void read_file(char * filename, char * data){
    FILE * fptr = fopen(filename, "w");
    if(fptr != NULL)
        fprintf(fptr, "%s", data);
    fclose(fptr);

}

char * write_file(char * filename, char * dest, int size){
    char cwd[256];
    char _filename[strlen(filename)];
    FILE * fptr;

    bzero(&_filename, strlen(filename));
    bzero(&cwd, 256);
    bzero(dest, size);

    strcpy(&_filename, filename);
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/tmp/");
    strcat(cwd, _filename);

    fptr = fopen(cwd, "r");
    if(fptr != NULL)
        fread(dest, 1, size, fptr);

    fclose(fptr);
    return dest;
}

// --- Directory functions

#define MAX_FILENAME_SIZE 25

struct directory_t {
    int num_files;
    char ** files;
};

int check_in_directory(char * filename, struct directory_t directory){
    for(int i = 0; i < directory.num_files; i++){
            if(strcmp(directory.files[i], filename) == 0) // match
            {
                return 1;
            }
        }

    return 0;
}

struct directory_t read_dir(){
    // read the downloads dir if it exists

    // if not return null
}

int create_dir(){
    // initialize the downloads dir

}

#endif //PEER2PEER_COMMON_H
