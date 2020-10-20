#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define BUFFER_LEN 100

int main() {

    int sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_LEN];

    bzero((char *)&server_addr, sizeof(server_addr));
    bzero((char *)&client_addr, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    int recv_len;
    recv_len = recvfrom(sock, buffer, BUFFER_LEN, 0, (struct sockaddr *)&client_addr,  sizeof(client_addr));
    printf("Received from %s %d Bytes \n", inet_ntoa(client_addr.sin_addr), recv_len);
    printf("Buffer: %s \n", buffer);

    char resp[] = "Return from serv :) ";
    strcat(resp, buffer);

    printf("Responding to client: %s", resp);

    sendto(sock, resp, sizeof(resp), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));

    bzero(buffer, BUFFER_LEN);
    if(recvfrom(sock, buffer, BUFFER_LEN, 0, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
        printf("????");

    close(sock);

    return 0;
}
