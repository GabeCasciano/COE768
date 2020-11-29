//
// Created by gabe on 2020-11-28.
//

#include "network.h"
#include "file_manipulation.h"

#define MAX_CONTENT_LIST_LEN 100

struct content_t content_list[MAX_CONTENT_LIST_LEN];

int index_server(struct sock_t sock, int is_server){
    // if content server
    if(is_server){

        if(sock.sockfd > 0){
            // is data reg
                // init if necessary
                // append to appropriate content list

            // is data dereg

        }
        if(sock.sockfd < 0){
            // dereg content from associated content server
        }

    }
        // else download client
    else{
        // all of the possible client commands
    }
}


int router(int arg, char * argv[]){
    // new process for each new connection
    struct sock_t sock = init_server_tcp(INDEX_PORT, LISTENERS);

    struct pdu_t pdu = init_pdu(PDU_WHOIS, " ");

    char * buff = (char *)malloc(MAX_DATA_LEN);
    serialized(pdu, buff);

    write(sock.sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    read(sock.sockfd, buff, sizeof(buff));
    unserialized(buff, &pdu);

    if(strcmp(pdu.data, "content") == 0){
        index_server(sock, 1);
    }
    else if(strcmp(pdu.data, "download") == 0){
        index_server(sock, 0);
    }
    else{
        // error
    }
}



