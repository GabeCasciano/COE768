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

    sendto(sock->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock->sockaddr, sock->sockaddr_len);
    bzero(buff, MAX_MSG_SIZE);
    recvfrom(sock->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock->sockaddr, &sock->sockaddr_len);
    unserialized(buff, &pdu);

    char ** datas = unserialized_data(pdu.data);

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

    serialized(pdu, buff);
    write(server.sockfd, buff, MAX_MSG_SIZE);
    bzero(buff, MAX_MSG_SIZE);
    read(server.sockfd, buff, MAX_MSG_SIZE);

    unserialized(buff, &pdu);

    if(pdu.type == PDU_CONTENT) {
        num_packs = atoi(pdu.data);
        file = (char *)malloc(MAX_MSG_SIZE * num_packs);
        bzero(file, MAX_MSG_SIZE * num_packs);

        pdu = init_pdu(PDU_ACK, " ");
        bzero(buff, MAX_MSG_SIZE);
        serialized(pdu, buff);
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

    close(server.sockfd);

}

void downloading_pt1(struct sock_t * sock){
    char * buff = (char *)malloc(MAX_MSG_SIZE);

    printf("Enter a filename to download (less than 20):\n");
    scanf("%s", buff);

    struct pdu_t pdu = init_pdu(PDU_REQUEST, buff);
    bzero(buff, MAX_MSG_SIZE);
    serialized(pdu, buff);

    sendto(sock->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock->sockaddr, sock->sockaddr_len);
    bzero(buff, MAX_MSG_SIZE);
    recvfrom(sock->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock->sockaddr, &sock->sockaddr_len);
    unserialized(buff, &pdu);

    char ** datas = unserialized_data(pdu.data);

    if(pdu.type == PDU_REQUEST){
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
    char * buff = (char *)malloc(MAX_MSG_SIZE);
    char ** datas = (char *)malloc(3);
    int num_files = 0;

    struct pdu_t pdu = init_pdu(PDU_LIST, " ");
    bzero(buff, MAX_MSG_SIZE);
    serialized(pdu, buff);

    sendto(sock->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock->sockaddr, sock->sockaddr_len);
    bzero(buff, MAX_MSG_SIZE);
    recvfrom(sock->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock->sockaddr, &sock->sockaddr_len);
    unserialized(buff, &pdu);

    if(pdu.type == PDU_LIST){
        num_files = atoi(pdu.data);
        printf("File List: \n");
        for(int i = 0; i < num_files; i++){
            bzero(buff, MAX_MSG_SIZE);
            recvfrom(sock->sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&sock->sockaddr, &sock->sockaddr_len);
            unserialized(buff, &pdu);
            datas = unserialized_data(pdu.data);
            printf("File %d; %s, from %s, %d\n", i, datas[0], datas[2], atoi(datas[1]));
        }

    }


}


void download_client(int * run){
    struct sock_t sock = init_client_udp(INDEX_PORT, INDEX_ADDR);
    struct pdu_t pdu = init_pdu(PDU_ACK, " ");

    int * running = run;
    while (*running == 0);// wait until registration is completed

    while (*running){
        char input_cmd;

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
            printf("Exiting...\n");
            *running = 0;
            close(sock.sockfd);
        }
        else{ // help
            printf("Welcome to GTOR\n\n");
            printf("    - H -> help window\n");
            printf("    - S -> search command, enter a file to be\nsearched for on the index sever\n");
            printf("    - D -> download command, enter a file to be\ndownloaded from a download server\n");
            printf("    - L -> list command, request a list of files from the index server\n");
        }

        input_cmd = NULL;
        getchar();
    }
}


#endif //APP_DOWNLOAD_CLIENT_H
