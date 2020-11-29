//
// Created by gabe on 2020-11-28.
//

#ifndef PEER2PEER_COMMON_HEADERS_H
#define PEER2PEER_COMMON_HEADERS_H

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

#define MAX_DATA_LEN 100

#define PDU_ACK 'A'
#define PDU_ERROR 'E'
#define PDU_REGISTER 'R'
#define PDU_REQUEST 'D'
#define PDU_SEARCH 'S'
#define PDU_DEREGISTER 'T'
#define PDU_CONTENT 'C'
#define PDU_LIST 'O'
#define PDU_WHOIS 'W'

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
    int data_length = MAX_DATA_LEN;
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


#endif //PEER2PEER_COMMON_HEADERS_H
