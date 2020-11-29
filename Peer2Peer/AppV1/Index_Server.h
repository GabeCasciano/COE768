//
// Created by gabe on 2020-11-18.
//

#ifndef PEER2PEER_SERVER_H
#define PEER2PEER_SERVER_H

#include "common.h"

#define DEFAULT_PORT 8080
#define DEFAULT_ADDR "0.0.0.0"
#define DEFAULT_CLIENTS 2;

#define MAX_CONTENT_SERVERS 100

struct server_parameters {
    int port;
    int num_clients;
    int clientfd;
};

struct content_server_t{
    int port;
    char * addr;
    char * server_alias;
    struct directory_t directory;
};


void router(){}

void send_to_client(int fd, struct pdu_t pdu, char * buffer){
    serialized(pdu, buffer);
    write(fd, buffer, PDU_DATA_LENGTH_DEFAULT);
}

struct content_server_t check_for_file(char * filename, struct content_server_t * content_server){
    struct content_server_t temp_loc;
    temp_loc.port = 0;
    for (int i = 0; i < MAX_CONTENT_SERVERS; i++){
        if(content_server[i].port != 0){ // not empty, is also safe to assume that it has files
            if(check_in_directory(filename, content_server[i].directory) == 1){
                memcpy(&temp_loc, &content_server[i], sizeof(struct content_server_t));
                return temp_loc;
            }
        }
    }
    return temp_loc;

}

int check_if_server_exists(int port, char * addr, struct content_server_t * content_server) {
    for (int i = 0; i < MAX_CONTENT_SERVERS; i++) {
        if (content_server[i].port != 0 && strcmp(content_server[i].addr, addr) == 0)
            return i;
    }
    return -1;
}

void index_server( struct server_parameters parameters){
    struct sock_t sock = init_server_tcp(parameters.port, parameters.num_clients);
    int clientfd = accept(sock.sockfd, (struct sockaddr *)NULL, (socklen_t * )NULL);

    struct content_server_t content_servers[MAX_CONTENT_SERVERS]; // initialize me
    int content_server_counter = 0;

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

            struct content_server_t loc = check_for_file(pdu.data, content_servers);

            if(loc.port != 0){ // has the data
                char * return_data = (char *)malloc(PDU_DATA_LENGTH_DEFAULT);
                sprintf(return_data, "%d;%s;%s", loc.port,loc.addr, pdu.data);
                pdu = init_pdu(PDU_SEARCH, return_data);
                free(return_data);
            }
            else{
                pdu = init_pdu(PDU_ERROR, "3");
            }
            send_to_client(clientfd, pdu, recv_buffer);


        }
        else if(pdu.type == PDU_REQUEST){
            pdu = init_pdu(PDU_REQUEST, "is a request");
            send_to_client(clientfd, pdu, recv_buffer);
        }
        else if(pdu.type == PDU_REGISTER){

            // place holders

            int port = atoi(strtok(pdu.data, ";"));
            char * addr = strtok(NULL, ";");
            char * filename = strtok(NULL, ";");

            // performs existance checks
            int server_index = check_if_server_exists(port, addr, content_servers) ;

            if(server_index > 0){ // if it exists
                // add content to server director
                content_servers[server_index].directory.num_files++;
                content_servers[server_index].directory.files = (char **)realloc(content_servers[server_index].directory.files,
                                                                                           content_servers[server_index].directory.num_files);

                content_servers[server_index].directory.files[content_servers[server_index].directory.num_files - 1 ]= (char *)malloc(MAX_FILENAME_SIZE);

                strcpy(content_servers[server_index].directory.files[0], filename);

            }
            else{
                // add content server
                content_server_counter++;
                content_servers[content_server_counter].port = port;

                content_servers[content_server_counter].addr = (char *)malloc(sizeof(addr));
                strcpy( content_servers[content_server_counter].addr, addr);

                content_servers[content_server_counter].directory.num_files = 1;
                content_servers[content_server_counter].directory.files = (char **)malloc(1);
                content_servers[content_server_counter].directory.files[0] = (char *)malloc(MAX_FILENAME_SIZE);

                strcpy(content_servers[content_server_counter].directory.files[0], filename);

            }

            free(addr);
            free(filename);

            // respond with an ack if successful
            pdu = init_pdu(PDU_ACK, "");
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
