//
// Created by gabe on 2020-12-05.
//

#include "../common.h"

#define CMD_SERVER "-s"
#define CMD_CLIENT "-c"

#define PORT 1234
#define ADDR "0.0.0.0"
int main(int argc, char * argv[]) {

    struct sock_t sock;
    if (argc > 1) {
        if (strcmp(argv[1], CMD_SERVER) == 0) {
            sock = init_server_udp(PORT);
            struct sock_t client;
            char * buff = (char *)malloc(MAX_MSG_SIZE);

            recvfrom(sock.sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client.sockaddr, &client.sockaddr_len);

            printf("From the client: %s \n", buff);
            bzero(buff, MAX_MSG_SIZE);
            sprintf(buff, "Hello from the udp server");
            sendto(sock.sockfd, buff, MAX_MSG_SIZE, 0, (struct sockaddr *)&client.sockaddr, client.sockaddr_len);


        } else if (strcmp(argv[1], CMD_CLIENT) == 0) {
            printf("Starting client \n");
            sock = init_client_udp(PORT, ADDR);

            char * buff = (char *)malloc(MAX_MSG_SIZE);
            sprintf(buff, "Hello fro the client");
            write(sock.sockfd, buff, MAX_MSG_SIZE);
            bzero(buff, MAX_MSG_SIZE);
            read(sock.sockfd, buff, MAX_MSG_SIZE);
            printf("from SERVER: %s \n", buff);
        }
    }
}