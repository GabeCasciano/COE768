//
// Created by gabe on 2020-12-05.
//

#ifndef PEER2PEER_PDUS_H
#define PEER2PEER_PDUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PDU_ACK 'A'
#define PDU_ERROR 'E'
#define PDU_REGISTER 'R'
#define PDU_REQUEST 'D'
#define PDU_SEARCH 'S'
#define PDU_DEREGISTER 'T'
#define PDU_CONTENT 'C'
#define PDU_LIST 'O'

#define ERR_EXIT 1
#define ERR_RESEND 2
#define ERR_NOFILE 3

#define MAX_ELEMENTS_PER_DATA 5
#define MAX_DATA_LEN 100
#define MAX_MSG_SIZE 102

struct pdu_t {
    char type;
    char * data;
};

struct packet_t {
    int length;
    struct pdu_t * pdus;
};

struct pdu_t init_pdu(const char type, char * data){
    struct pdu_t pdu;

    pdu.type = type;
    pdu.data = (char *)malloc(MAX_DATA_LEN);

    if(data != NULL){
        strcpy(pdu.data, (char*)data);
    }

    return pdu;
}

char * serialized(struct pdu_t pdu, char * dest){
    sprintf(dest, "%c", pdu.type);
    strcat(dest, ",");
    strncat(dest, pdu.data, MAX_DATA_LEN);

    return dest;
}

struct pdu_t unserialized(char * cereal, struct pdu_t * pdu){

    pdu->type = cereal[0];
    bzero(pdu->data, MAX_DATA_LEN);
    strncpy(pdu->data, cereal+2, MAX_DATA_LEN);

    return *pdu;
}

char ** unserialized_data(char * data){
    char ** datas = (char **)malloc(MAX_ELEMENTS_PER_DATA);

    if(data != NULL) {
        char *holder = strtok(data, ";");
        for (int i = 0; i < MAX_ELEMENTS_PER_DATA; i++) {
            if (holder != NULL) {
                datas[i] = (char *) malloc(MAX_FILENAME_LEN);
                strcpy(datas[i], holder);
                holder = strtok(NULL, ";");
            } else
                break;
        }
    }
    return datas;
}

char * serialized_data(char ** data, int size){

    char * output = (char *)malloc(MAX_FILENAME_LEN * size);
    for(int i = 0; i < size; i++){
        if(data[i] != NULL) {
            strcat(output, data[i]);
        }
        else{
            strcat(output, " ");
        }
        strcat(output, ";");
    }

    return output;

}

struct packet_t init_packet(int packet_data_size, char * data, int data_length){
    struct packet_t packet;
    packet.length = (data_length/packet_data_size) + (data_length % packet_data_size != 0);
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

#endif //PEER2PEER_PDUS_H
