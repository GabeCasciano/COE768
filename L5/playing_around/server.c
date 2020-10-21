//
// Created by gabe on 2020-10-21.
//

#include "../common.h"

#define port 8080

int main(){
    int recv_len;
    struct sock_t server, client;
    struct pdu_t pdu;

    char *buffer;

    buffer = (char *)malloc(PDU_DATA_LEN + 2);

    client.sockaddr_len = sizeof(client.sockaddr);
    pdu.data = (char *)malloc(PDU_DATA_LEN);

    server = init_server(port);
    recv_len = recvfrom(server.sockfd, buffer, PDU_DATA_LEN + 2, 0, (struct sockaddr *)&client.sockaddr, &client.sockaddr_len);

    printf("Received from %s %d Bytes \n", inet_ntoa(client.sockaddr.sin_addr), recv_len);
    printf("Buffer: %s \n", unserialized(buffer).data);

    close(server.sockfd);

    return 0;
}