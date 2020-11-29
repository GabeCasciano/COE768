//
// Created by gabe on 2020-11-28.
//

#include "network.h"
#include "file_manipulation.h"


int download_client(){
    struct sock_t sock = init_tcp_client(INDEX_PORT, INDEX_ADDR);
    char * buff = (char *)malloc(MAX_DATA_LEN);
    struct pdu_t pdu = init_pdu(PDU_WHOIS, "download");

    // -- init sequence

    read(sock.sockfd, buff, MAX_DATA_LEN);
    if(buff[0] != 'W') // server is not asking who is
        return -1;

    serialized(pdu, buff);
    write(sock.sockfd, buff, MAX_DATA_LEN);



}