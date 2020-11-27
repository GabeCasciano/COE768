//
// Created by gabe on 2020-11-18.
//

#ifndef PEER2PEER_SERVER_H
#define PEER2PEER_SERVER_H

#include "common.h"

#define DEFAULT_PORT 8080
#define DEFAULT_ADDR "0.0.0.0"
#define DEFAULT_CLIENTS 2;

struct server_parameters {
    int port;
    int num_clients;
    int clientfd;
};

void router(){}

void send_to_client(int fd, struct pdu_t pdu, char * buffer){
    serialized(pdu, buffer);
    write(fd, buffer, PDU_DATA_LENGTH_DEFAULT);
}

void index_server( struct server_parameters parameters){
    struct sock_t sock = init_server_tcp(parameters.port, parameters.num_clients);
    int clientfd = accept(sock.sockfd, (struct sockaddr *)NULL, (socklen_t * )NULL);


    struct pdu_t pdu = init_pdu("a", "");
    char * recv_buffer = (char *) malloc(PDU_DATA_LENGTH_DEFAULT + 1);

    if (clientfd > 0) { // sock is init properly
        read(clientfd, recv_buffer, PDU_DATA_LENGTH_DEFAULT + 1);
        unserialized(recv_buffer, &pdu);

        if(pdu.type == PDU_LIST){
            pdu = init_pdu(PDU_LIST, "is a list");
            send_to_client(clientfd, pdu, recv_buffer);
        }
        else if(pdu.type == PDU_SEARCH){
            pdu = init_pdu(PDU_SEARCH, "is a search");
            send_to_client(clientfd, pdu, recv_buffer);
        }
        else if(pdu.type == PDU_REQUEST){
            pdu = init_pdu(PDU_REQUEST, "is a request");
            send_to_client(clientfd, pdu, recv_buffer);
        }
        else if(pdu.type == PDU_REGISTER){
            pdu = init_pdu(PDU_REGISTER, "is a reg");
            send_to_client(clientfd, pdu, recv_buffer);
        }
        else if(pdu.type == PDU_DEREGISTER){
            pdu = init_pdu(PDU_DEREGISTER, "is a dereg");
            send_to_client(clientfd, pdu, recv_buffer);
        }
        else if(pdu.type == PDU_ACK){
            pdu = init_pdu(PDU_ACK, "is a ACK");
            send_to_client(clientfd, pdu, recv_buffer);
        }
        else if(pdu.type == PDU_ERROR){
            pdu = init_pdu(PDU_ERROR, "is a error");
            send_to_client(clientfd, pdu, recv_buffer);
        }

    }

    //kill connection with client
    //send goodbye, and set internal_running = 0;
    close(sock.sockfd);
    free(recv_buffer);
    exit(1);
}

#endif //PEER2PEER_SERVER_H
