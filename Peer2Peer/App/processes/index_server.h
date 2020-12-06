//
// Created by gabe on 2020-12-05.
//

#ifndef APP_INDEX_SERVER_H
#define APP_INDEX_SERVER_H

#include "../common.h"

#define CONTENT_LIST_LEN 10

struct content_t content[CONTENT_LIST_LEN];
int content_counter  = 0;

void do_register(struct pdu_t pdu, char * addr){

    char ** data = unserialized_data(pdu.data);

    int index = find_server_with_addr(content, CONTENT_LIST_LEN, addr);

    if(data[0] != NULL && data[1] != NULL) {
        if (index == -1) {
            if(content_counter < CONTENT_LIST_LEN) {
                content[content_counter] = init_content(atoi(data[1]), addr);
                add_content(&content[content_counter], data[0]);

                content_counter++;
            }
        } else {
            add_content(&content[index], data[0]);
        }
    }

    data = NULL;
    free(data);

}

void do_unregister(struct pdu_t pdu, char * addr){
    char ** data = unserialized_data(pdu.data);

    int index = find_server_with_addr(content, CONTENT_LIST_LEN, addr);

    if(data[0] != NULL && data[1] != NULL) {

        if (index >= 0){
            remove_content(&content[index], data[0]);
        }

    }

    data = NULL;
    free(data);
}

void do_search(struct pdu_t pdu, struct sock_t * server, struct sock_t * client){
    int index = find_server_with_file(content, CONTENT_LIST_LEN, pdu.data);
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t send_pdu;
    char ** datas = (char **)malloc(3);

    if(index >= 0){

        datas[0] = (char *)malloc(MAX_FILENAME_LEN);
        datas[1] = (char *)malloc(MAX_FILENAME_LEN);
        datas[2] = (char *)malloc(MAX_FILENAME_LEN);

        strcpy(datas[0], pdu.data);
        sprintf(datas[1], "%d", DOWNLOAD_PORT);
        strcpy(datas[2], content[index].addr);

        bzero(buff, MAX_MSG_SIZE);
        buff = serialized_data(datas, 3);
        send_pdu = init_pdu(PDU_SEARCH, buff);
        serialized(send_pdu, buff);
    }
    else{
        sprintf(buff, "%d", ERR_NOFILE);
        send_pdu = init_pdu(PDU_ERROR, buff);
        bzero(buff, MAX_MSG_SIZE);
        serialized(send_pdu, buff);
    }

    sendto(server->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client->sockaddr, client->sockaddr_len);

    datas = NULL;
    buff = NULL;
    free(buff);
    free(datas);



}

void do_request(struct pdu_t pdu, struct sock_t * server, struct sock_t * client){
    int index = find_server_with_file(content, CONTENT_LIST_LEN, pdu.data);
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t send_pdu;
    char ** datas = (char **)malloc(3);

    if(index >= 0){

        datas[0] = (char *)malloc(MAX_FILENAME_LEN);
        datas[1] = (char *)malloc(MAX_FILENAME_LEN);
        datas[2] = (char *)malloc(MAX_FILENAME_LEN);

        strcpy(datas[0], pdu.data);
        sprintf(datas[1], "%d", DOWNLOAD_PORT);
        strcpy(datas[2], content[index].addr);

        bzero(buff, MAX_MSG_SIZE);
        buff = serialized_data(datas, 3);
        send_pdu = init_pdu(PDU_REQUEST, buff);
        serialized(send_pdu, buff);
    }
    else{
        sprintf(buff, "%d", ERR_NOFILE);
        send_pdu = init_pdu(PDU_ERROR, buff);
        bzero(buff, MAX_MSG_SIZE);
        serialized(send_pdu, buff);
    }

    sendto(server->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client->sockaddr, client->sockaddr_len);

    datas = NULL;
    buff = NULL;
    free(buff);
    free(datas);
}

void do_list(struct sock_t * server, struct sock_t * client){
    int pdu_to_send = 0;
    char * buff = (char *)malloc(MAX_MSG_SIZE);

    bzero(buff, MAX_MSG_SIZE);

    for(int i = 0; i < content_counter; i++)
        pdu_to_send += content[i].num_files;

    sprintf(buff, "%d", pdu_to_send);
    struct pdu_t send_pdu = init_pdu(PDU_LIST, buff);
    serialized(send_pdu, buff);
    sendto(server->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client->sockaddr, client->sockaddr_len);

    for(int i = 0; i < content_counter; i++){
        for(int j = 0; j < content[i].num_files; j++) {
            char **datas = (char **) malloc(3);

            datas[0] = (char *) malloc(MAX_FILENAME_LEN);
            datas[1] = (char *) malloc(MAX_FILENAME_LEN);
            datas[2] = (char *) malloc(MAX_FILENAME_LEN);

            strcpy(datas[0], content[i].files[j]);
            sprintf(datas[1], "%d", content[i].port);
            strcpy(datas[2], content[i].addr);

            bzero(buff, MAX_MSG_SIZE);
            buff = serialized_data(datas, 3);
            send_pdu = init_pdu(PDU_LIST, buff);
            serialized(send_pdu, buff);

            sendto(server->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client->sockaddr, client->sockaddr_len);

            datas = NULL;
            free(datas);
        }
    }
    buff = NULL;
    free(buff);

}

void index_server(){
    struct sock_t server = init_server_udp(INDEX_PORT);


    int running = 1;

    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t recv_pdu = init_pdu(PDU_ACK, " ");

    while(running){
        struct sock_t client = init_udp_server_cli();
        recvfrom(server.sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client.sockaddr, &client.sockaddr_len);
        unserialized(buff, &recv_pdu);
        client.addr = inet_ntoa(client.sockaddr.sin_addr);

        // socket is dying around here somewhere

        if(recv_pdu.type == PDU_REGISTER){
            do_register(recv_pdu, client.addr);
        }
        else if(recv_pdu.type == PDU_DEREGISTER){
            do_unregister(recv_pdu, client.addr);
        }
        else if(recv_pdu.type == PDU_SEARCH){
            do_search(recv_pdu, &server, &client);
        }
        else if(recv_pdu.type == PDU_REQUEST){
            do_request(recv_pdu, &server, &client);
        }
        else if(recv_pdu.type == PDU_LIST){
            do_list(&server, &client);
        }
        else if(recv_pdu.type == PDU_ERROR){
            if (recv_pdu.data == ERR_EXIT)
                running = 0;
        }
        bzero(buff, MAX_MSG_SIZE);
    }

}

#endif //APP_INDEX_SERVER_H
