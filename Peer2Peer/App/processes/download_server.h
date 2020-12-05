//
// Created by gabe on 2020-12-05.
//

#ifndef APP_DOWNLOAD_SERVER_H
#define APP_DOWNLOAD_SERVER_H

#include "../common.h"

void do_registration(struct sock_t sock){
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t pdu;

    struct cwd_t cwd = read_cwd();

    for(int i = 0; i < cwd.num_files; i++){

        char ** datas = (char **)malloc(2);
        datas[0] = (char *)malloc(MAX_FILENAME_LEN);
        datas[1] = (char *)malloc(MAX_FILENAME_LEN);
        strcpy(datas[0], cwd.files[i]);
        sprintf(datas[1], "%d", DOWNLOAD_PORT);

        bzero(buff, MAX_MSG_SIZE);
        buff = serialized_data(datas, 2);

        pdu = init_pdu(PDU_REGISTER, buff);
        serialized(pdu, buff);
        write(sock.sockfd, buff, MAX_MSG_SIZE);

        datas = NULL;
        free(datas);
    }
}

void do_unregistration(struct sock_t sock){
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t pdu;

    struct cwd_t cwd = read_cwd();

    for(int i = 0; i < cwd.num_files; i++){
        char ** datas = (char **)malloc(2);
        datas[0] = (char *)malloc(MAX_FILENAME_LEN);
        datas[1] = (char *)malloc(MAX_FILENAME_LEN);
        strcpy(datas[0], cwd.files[i]);
        sprintf(datas[1], "%d", DOWNLOAD_PORT);

        bzero(buff, MAX_MSG_SIZE);
        buff = serialized_data(datas, 2);

        pdu = init_pdu(PDU_DEREGISTER, buff);
        serialized(pdu, buff);
        write(sock.sockfd, buff, MAX_MSG_SIZE);

        datas = NULL;
        free(datas);
    }
}

void download_server(){
    struct sock_t sock = init_client_udp(INDEX_PORT, INDEX_ADDR);
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t pdu = init_pdu(PDU_ACK, " ");

    int running = 1;

    do_registration(sock);

    while (running){

    }

    do_unregistration(sock);

    buff = NULL;
    free(buff);
    close(sock.sockfd);
}

#endif //APP_DOWNLOAD_SERVER_H
