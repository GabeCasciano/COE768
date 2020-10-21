//
// Created by gabe on 2020-10-21.
//

#ifndef L5_COMMON_H
#define L5_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//  --  PDU STUFF  --

#define PDU_DATA_LEN 100

#define PDU_TYPE_ACK 'A'
#define PDU_TYPE_DATA 'D'
#define PDU_TYPE_FINAL 'F'
#define PDU_TYPE_ERROR 'E'
#define PDU_TYPE_FILENAME 'C'

struct pdu_t{
    char type;
    char* data; // allocate space as needed, no larger than PDU_DATA_LEN, but can be less
};

struct packed_t{
    struct pdu_t * pdu;
    int num_packets;
};

struct packed_t strpack(char * src, int len){
    //control variables to determine packing
    struct packed_t packets;
    int rem = ((len % PDU_DATA_LEN) > 0?1:0), rem_len = len;
    packets.num_packets = (len / PDU_DATA_LEN) + rem;

    packets.pdu = (struct pdu_t *)calloc(packets.num_packets, sizeof(struct pdu_t));


    for(int i = 0; i < packets.num_packets; i++){
        int bytes_write = (rem_len > PDU_DATA_LEN)? PDU_DATA_LEN : rem_len;

        packets.pdu[i].data = (char *)calloc(bytes_write, sizeof(char));
        packets.pdu[i].type = PDU_TYPE_DATA;
        bzero(packets.pdu[i].data, bytes_write);
        strncpy(packets.pdu[i].data, src + (len - rem_len), bytes_write);
        rem_len -= bytes_write;
    }

    return packets;
}

char * serialized(struct pdu_t pdu, char * dest){
    dest = (char *)realloc(dest, strlen(pdu.data)  + 2);
    bzero(dest, sizeof(pdu.data) + 2);

    dest[0] = pdu.type;
    strcat(dest, ",");
    strcat(dest, pdu.data);

    dest = strdup(dest);
    return dest;
}

struct pdu_t unserialized(char * cereal, struct pdu_t * pdu){

    pdu->type = cereal[0];
    bzero(pdu->data, strlen(cereal));
    strncpy(pdu->data, cereal+2, strlen(cereal));

    return *pdu;
}

//  --  SOCKET STUFF  --

struct sock_t{
    int sockfd;
    struct sockaddr_in sockaddr;
    socklen_t sockaddr_len;
};

struct sock_t init_client(char* host, int port){
    struct sock_t sock;
    bzero((char *)&sock.sockaddr, sizeof(sock.sockaddr));
    sock.sockaddr_len = sizeof(sock.sockaddr);

    sock.sockaddr.sin_family = AF_INET;
    sock.sockaddr.sin_port = htons(port);
    inet_aton(host, &sock.sockaddr.sin_addr);

    sock.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    connect(sock.sockfd, (struct sockaddr *)&sock.sockaddr, sock.sockaddr_len);

    return sock;
}

struct sock_t init_server(int port){
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

//  --  FILE OPS  --

int filesize(char * filename){
    char cwd[256];
    bzero(cwd, 256);

    struct stat st;
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/tmp/");
    strcat(cwd, filename);

    if(stat(cwd, &st) != -1)
        return st.st_size;
    return -1;

}


char * file_to_string(char * filename, char * dest, int size){
    char cwd[256];
    FILE * fptr;

    dest = (char *)malloc(size);

    bzero(cwd, 256);
    bzero(dest, size);

    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/tmp/");
    strcat(cwd, filename);

    fptr = fopen(cwd, "r");
    if(fptr != NULL)
        fread(dest, 1, size, fptr);

    fclose(fptr);
    free(fptr);
    return dest;
}

void string_to_file(char * filename, char * src){
    char cwd[256];
    FILE * fptr;

    bzero(cwd, 256);

    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/");
    strcat(cwd, filename);

    fptr = fopen(cwd, "w");
    if(fptr != NULL)
        fwrite(src, 1, strlen(src), fptr);

    fclose(fptr);

}



#endif //L5_COMMON_H
