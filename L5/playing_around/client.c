//
// Created by gabe on 2020-10-21.
//

#include "common.h"

#define host "127.0.0.1"
#define port 8080

int main(){
    struct sock_t server;
    struct pdu_t pdu;
    char * buffer;

    pdu.data = (char *)malloc(PDU_DATA_LEN);
    pdu.type = 'D';
    pdu.data = "Hello from the client, how are you server?";

    server = init_client(host, port);
    buffer = serialized(pdu, buffer);
    write(server.sockfd, buffer, strlen(buffer));
    printf("%d",strlen(buffer));

    close(server.sockfd);

    return 0;


}