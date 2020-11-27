//
// Created by gabe on 2020-11-18.
//

#ifndef PEER2PEER_CLIENT_H
#define PEER2PEER_CLIENT_H

#define CMD_LIST 'L'
#define CMD_SEARCH 'S'
#define CMD_DOWNLOAD 'D'
#define CMD_EXIT 'E'

#include "common.h"

struct client_parameters {
    int port;
    char * host;
};

void content_server( int * running, struct client_parameters parameters){
    struct directory_t dir;
    int last_size = 0;

    while(running) {
        dir = read_dir();
        if (dir.num_files > 0) {
            //update index server if necessary
            //be available for transmit
        }
    }
    // unregister all content

}


void download_client( struct  client_parameters parameters){
    struct sock_t sock_tcp; // = init_tcp_client(parameters.port, parameters.host);
    struct sock_t sock_udp;
    struct pdu_t pdu;

    char * recv_buffer = (char *) malloc(PDU_DATA_LENGTH_DEFAULT + 1);

        char command;

        printf("Please enter a command: ");
        scanf("%c", &command);
        command = toupper(command);
        sock_tcp = init_tcp_client(parameters.port, parameters.host);
        // connect to the index server at a dedicated addr and port

        if (command == CMD_LIST) {
            // signal to the index server that we would like the list of content available
            pdu = init_pdu(PDU_LIST, " ");
            serialized(pdu, recv_buffer);

            write(sock_tcp.sockfd, recv_buffer, PDU_DATA_LENGTH_DEFAULT + 1);
            bzero(recv_buffer, PDU_DATA_LENGTH_DEFAULT);
            read(sock_tcp.sockfd, recv_buffer, PDU_DATA_LENGTH_DEFAULT);

            printf("%s", recv_buffer);

        }
        else if(command == CMD_SEARCH) {

        }
        else if(command == CMD_DOWNLOAD){

        }
        else if(command == CMD_EXIT){
            // send an error code 0 for exit
        }

    free(recv_buffer);
    close(sock_tcp.sockfd);

}


#endif //PEER2PEEServer_CLIENT_H
