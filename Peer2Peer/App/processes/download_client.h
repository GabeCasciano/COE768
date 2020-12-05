//
// Created by gabe on 2020-12-05.
//

#ifndef APP_DOWNLOAD_CLIENT_H
#define APP_DOWNLOAD_CLIENT_H

#define CMD_SEARCH 'S'
#define CMD_REQUEST 'D'
#define CMD_LIST 'L'
#define CMD_EXIT 'E'
#define CMD_HELP 'H'

#include <ctype.h>
#include "../common.h"

void searching(struct sock_t * sock){
    char * buff = (char *)malloc(MAX_MSG_SIZE);

    printf("Enter a filename to search (less than 20):\n");
    scanf("%s", buff);

    struct pdu_t pdu = init_pdu(PDU_SEARCH, buff);
    bzero(buff, MAX_MSG_SIZE);
    serialized(pdu, buff);

    write(sock->sockfd, buff, MAX_MSG_SIZE);
    bzero(buff, MAX_MSG_SIZE);
    read(sock->sockfd, buff, MAX_MSG_SIZE);
    unserialized(buff, &pdu);

    char ** datas = unserialized_data(buff);

    if(pdu.type == PDU_SEARCH){
        printf("Server has file: %s, on download server %s at port %d\n", datas[0], datas[2], atoi(datas[1]));
    }
    else
        printf("Server does not have specified file\n");

    buff = NULL;
    free(buff);

}

void downloading_pt2(char * filename, char * addr,  int port){
    struct sock_t server = init_tcp_client(port, addr);
    struct pdu_t pdu = init_pdu(PDU_REQUEST, filename);

    char * buff = (char *)malloc(MAX_MSG_SIZE);
    char * file;
    int num_packs = 0;

    serialized(pdu, filename);
    write(server.sockfd, buff, MAX_MSG_SIZE);
    bzero(buff, MAX_MSG_SIZE);
    read(server.sockfd, buff, MAX_MSG_SIZE);

    unserialized(buff, &pdu);

    if(pdu.type == PDU_CONTENT) {
        num_packs = atoi(pdu.data);
        file = (char *)malloc(MAX_MSG_SIZE * num_packs);

        pdu = init_pdu(PDU_ACK, " ");
        serialized(pdu, filename);
        write(server.sockfd, buff, MAX_MSG_SIZE);

        for(int i = 0; i < num_packs; i++){
            bzero(buff, MAX_MSG_SIZE);
            read(server.sockfd, buff, MAX_MSG_SIZE);
            strcat(file, buff);
        }

        write_file(filename, file);
        printf("Successful download from %s\n", addr);

    }

    file = NULL;
    buff = NULL;
    free(file);
    free(buff);

}

void downloading_pt1(struct sock_t * sock){
    char * buff = (char *)malloc(MAX_MSG_SIZE);

    printf("Enter a filename to download (less than 20):\n");
    scanf("%s", buff);

    struct pdu_t pdu = init_pdu(PDU_REQUEST, buff);
    bzero(buff, MAX_MSG_SIZE);
    serialized(pdu, buff);

    write(sock->sockfd, buff, MAX_MSG_SIZE);
    bzero(buff, MAX_MSG_SIZE);
    read(sock->sockfd, buff, MAX_MSG_SIZE);
    unserialized(buff, &pdu);

    char ** datas = unserialized_data(buff);

    if(pdu.type == PDU_SEARCH){
        printf("Server has file: %s, on download server %s at port %d\n", datas[0], datas[2], atoi(datas[1]));
        printf("Beginning download\n");
        downloading_pt2(datas[0], datas[2], atoi(datas[1]));
    }
    else
        printf("Server does not have specified file\n");

    buff = NULL;
    free(buff);
}


void listing(struct sock_t * sock){

}


void download_client(){
    struct sock_t sock = init_client_udp(INDEX_PORT, INDEX_ADDR);
    struct pdu_t pdu = init_pdu(PDU_ACK, " ");

    int running = 1;
    char input_cmd;

    while (running){
        printf("Enter a command:\n");
        scanf("%c", &input_cmd);

        input_cmd = toupper(input_cmd);

        if(input_cmd == CMD_SEARCH){
            searching(&sock);
        }
        else if(input_cmd == CMD_LIST){
            listing(&sock);
        }
        else if(input_cmd == CMD_REQUEST){
            downloading_pt1(&sock);
        }
        else if(input_cmd == CMD_EXIT){
            running = 0;
        }
        else{ // help

        }


    }
}


#endif //APP_DOWNLOAD_CLIENT_H
