#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define IP "127.0.0.1"
#define PORT 8080
#define BUFFER_LEN 100

int main() {

    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_LEN];

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_aton(IP, &server_addr.sin_addr);

    printf("Enter a message \n");
    fgets(buffer, BUFFER_LEN, stdin);

    if(sendto(sock, buffer, BUFFER_LEN, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        printf("????");

    bzero(buffer, BUFFER_LEN);
    int recv_len;

    recv_len = recvfrom(sock, buffer, BUFFER_LEN, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));


    printf("Received from %s, %d Bytes \n", inet_ntoa(server_addr.sin_addr), recv_len);
    printf("Buffer: %s", buffer);

    close(sock);
    return 0;
}