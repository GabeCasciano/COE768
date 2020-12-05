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

void do_file_transfer(){
    struct sock_t server = init_server_tcp(DOWNLOAD_PORT, 1);
    struct sock_t client;
    struct pdu_t pdu = init_pdu(PDU_ACK, " ");

    char * buff = (char *)malloc(MAX_MSG_SIZE);
    char * file;

    client.sockfd = accept(server.sockfd, (struct sockaddr *)&client.sockaddr, (socklen_t *)&client.sockaddr_len);
    bzero(buff, MAX_MSG_SIZE);
    read(client.sockfd, buff, MAX_MSG_SIZE);
    unserialized(buff, &pdu);

    if(file_in_cwd(pdu.data)){
        int size = filesize(pdu.data);
        file = (char *)malloc(size);
        read_file(pdu.data, file, size);

        struct packet_t packs = init_packet(MAX_DATA_LEN, file, strlen(file));
        pdu = init_pdu(PDU_CONTENT, packs.length + '0');
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
    close(server.sockfd);

}

void download_server(){
    struct sock_t sock = init_client_udp(INDEX_PORT, INDEX_ADDR);
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t pdu = init_pdu(PDU_ACK, " ");

    int running = 1;

    do_registration(sock);

    while (running){
        do_file_transfer();
    }

    do_unregistration(sock);

    buff = NULL;
    free(buff);
    close(sock.sockfd);
}

#endif //APP_DOWNLOAD_SERVER_H
