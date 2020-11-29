//
// Created by gabe on 2020-11-28.
//

#include "network.h"
#include "file_manipulation.h"

int do_data_register_seq(struct sock_t sock){
    // register all content to the index server
    // read directory into content_t struct
    // send to index server

}

int do_data_deregister_seq(struct sock_t sock){
    // unregister all content from the index server
    // tell index server to dereg from bottom to top data from content_t struct
}


int content_server(){
    struct sock_t sock = init_tcp_client(INDEX_PORT, INDEX_ADDR);
    char * buff = (char *)malloc(MAX_DATA_LEN);
    struct pdu_t pdu = init_pdu(PDU_WHOIS, "content");

    // -- init sequence

    read(sock.sockfd, buff, MAX_DATA_LEN);
    if(buff[0] != 'W') // server is not asking who is
        return -1;

    serialized(pdu, buff);
    write(sock.sockfd, buff, MAX_DATA_LEN);

    // register all our data


}

