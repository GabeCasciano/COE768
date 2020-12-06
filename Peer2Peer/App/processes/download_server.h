//
// Created by gabe on 2020-12-05.
//

#ifndef APP_DOWNLOAD_SERVER_H
#define APP_DOWNLOAD_SERVER_H

#include "../common.h"

void do_registration(){
    struct sock_t sock = init_client_udp(INDEX_PORT, INDEX_ADDR);
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
        sendto(sock.sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock.sockaddr, sock.sockaddr_len);
        //write(sock->sockfd, buff, MAX_MSG_SIZE);

        datas = NULL;
        free(datas);
    }

    printf("Completed registration\n");
}

void do_unregistration(){
    struct sock_t sock = init_client_udp(INDEX_PORT, INDEX_ADDR);
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
        sendto(sock.sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock.sockaddr, sock.sockaddr_len);

        datas = NULL;
        free(datas);
    }
    printf("Completed deregistration\n");
}

void do_file_transfer(struct sock_t server){

    struct sock_t client;
    struct pdu_t pdu = init_pdu(PDU_ACK, " ");

    char * buff = (char *)malloc(MAX_MSG_SIZE);
    char * file;

    client.sockfd = accept(server.sockfd, (struct sockaddr *)NULL, (socklen_t *)NULL);
    bzero(buff, MAX_MSG_SIZE);
    read(client.sockfd, buff, MAX_MSG_SIZE);
    unserialized(buff, &pdu);

    if(file_in_cwd(pdu.data) >= 0 && pdu.type == PDU_REQUEST){
        int size = filesize(pdu.data);
        file = (char *)malloc(size);
        read_file(pdu.data, file, size);

        size = strlen(file);
        struct packet_t packs = init_packet(MAX_DATA_LEN, file, size);
        bzero(buff, MAX_MSG_SIZE);
        sprintf(buff, "%d", packs.length);
        pdu = init_pdu(PDU_CONTENT, buff);
        bzero(buff, MAX_MSG_SIZE);
        serialized(pdu, buff);

        write(client.sockfd, buff, MAX_MSG_SIZE);
        bzero(buff, MAX_MSG_SIZE);
        read(client.sockfd, buff, MAX_MSG_SIZE);
        unserialized(buff, &pdu);

        if(pdu.type == PDU_ACK){
            for(int i = 0; i < packs.length; i++){
                bzero(buff, MAX_MSG_SIZE);
                serialized(packs.pdus[i], buff);
                write(client.sockfd, buff, MAX_MSG_SIZE);
            }
        }

    }

    buff = NULL;
    file = NULL;
    free(buff);
    free(file);
    close(client.sockfd);

}

void * download_server(){

    struct sock_t server;
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t pdu = init_pdu(PDU_ACK, " ");

    printf("Starting download server \n");
    int running =1 ;
    server = init_server_tcp(DOWNLOAD_PORT, 1);

    while (running){
        do_file_transfer(server);
    }

    close(server.sockfd);


    buff = NULL;
    free(buff);
}

#endif //APP_DOWNLOAD_SERVER_H
