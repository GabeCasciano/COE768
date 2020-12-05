//
// Created by gabe on 2020-12-05.
//

#ifndef APP_INDEX_SERVER_H
#define APP_INDEX_SERVER_H

#include "../common.h"

#define CONTENT_LIST_LEN 10

struct content_t content[CONTENT_LIST_LEN];
int content_counter  = 0;

void do_register(struct pdu_t pdu, struct sock_t server, struct sock_t client){
    struct pdu_t send_pdu = init_pdu(PDU_ACK, " ");
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    char ** data = unserialized_data(pdu.data);
    char * addr = inet_ntoa(client.sockaddr.sin_addr);
    int index = find_server_with_addr(content, CONTENT_LIST_LEN, addr);
    if(data[0] != NULL && data[1] != NULL) {
        if (index > -1) {
            add_content(&content[index], data[0]);
            content_counter++;
        } else {
            content[index] = init_content(data[1], addr);
            add_content(&content[index], data[0]);
        }
    }

    bzero(buff, MAX_MSG_SIZE);
    serialized(send_pdu, buff);
    sendto(server.sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr*)&client.sockaddr, client.sockaddr_len);

    free(data);
    free(addr);
    free(buff);

}

void do_unregister(struct pdu_t pdu, struct sock_t server, struct sock_t client){

}

void do_search(struct pdu_t pdu, struct sock_t server, struct sock_t client){

}

void do_request(struct pdu_t pdu, struct sock_t server, struct sock_t client){

}

void do_list(){

}

void index_server(){
    struct sock_t server = init_server_udp(INDEX_PORT);
    struct sock_t client;

    char * buff = (char *)malloc(MAX_MSG_SIZE);
    struct pdu_t recv_pdu = init_pdu(PDU_ACK, " ");
    struct pdu_t send_pdu = init_pdu(PDU_ACK, " ");

    recvfrom(server.sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client.sockaddr, &client.sockaddr_len);
    unserialized(buff, &recv_pdu);

    if(recv_pdu.type == PDU_REGISTER){
        do_register(recv_pdu, server, client);
    }
    else if(recv_pdu.type == PDU_DEREGISTER){
        do_unregister(recv_pdu, server, client);
    }
    else if(recv_pdu.type == PDU_SEARCH){
        do_search(recv_pdu, server, client);
    }
    else if(recv_pdu.type == PDU_REQUEST){
        do_request(recv_pdu, server, client);
    }
    else if(recv_pdu.type == PDU_LIST){
        do_list(recv_pdu, server, client);
    }
    else if(recv_pdu.type == PDU_ERROR){

    }
    
    

}

#endif //APP_INDEX_SERVER_H
