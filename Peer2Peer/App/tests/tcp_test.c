//
// Created by gabe on 2020-12-05.
//

#include "../common.h"

#define CMD_SERVER "-s"
#define CMD_CLIENT "-c"

#define PORT 1234
#define ADDR "0.0.0.0"
int main(int argc, char * argv[]){

    struct sock_t sock;
    if(argc > 1){
        if(strcmp(argv[1], CMD_SERVER)==0) {
            printf("Starting server \n");
            sock = init_server_tcp(PORT, 1);

            struct sock_t client;

            client.sockfd = accept(sock.sockfd, (struct sockaddr *)&client.sockaddr, (socklen_t *)&client.sockaddr_len);

            char * buff = (char *) malloc(MAX_MSG_SIZE);
            read(client.sockfd, buff, MAX_MSG_SIZE);
            printf("from client: %s \n", buff);

            bzero(buff, MAX_MSG_SIZE);
            sprintf(buff, "Hello fro the server");
            write(client.sockfd, buff, MAX_MSG_SIZE);

            close(client.sockfd);
        }
        else if(strcmp(argv[1], CMD_CLIENT)==0) {
            printf("Starting client \n");
            sock = init_tcp_client(PORT, ADDR);

            char * buff = (char *)malloc(MAX_MSG_SIZE);
            sprintf(buff, "Hello fro the client");
            write(sock.sockfd, buff, MAX_MSG_SIZE);
            bzero(buff, MAX_MSG_SIZE);
            read(sock.sockfd, buff, MAX_MSG_SIZE);
            printf("from SERVER: %s \n", buff);

        }
    }

    close(sock.sockfd);

}

