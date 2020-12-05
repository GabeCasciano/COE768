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

    
}

void do_unregistration(struct sock_t sock){

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

}

#endif //APP_DOWNLOAD_SERVER_H
