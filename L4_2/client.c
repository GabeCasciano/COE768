//
// Created by gabriel on 2020-10-13.
//

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

#define SERVER_TCP_PORT 8080
#define BUFFER_LEN 256
#define PACKET_LEN 100

int main(int argc, char **argv) {
    char *host, *filename, buffer[BUFFER_LEN];
    int port, sock, n, chunks;
    struct sockaddr_in addr;
    struct hostent *hostp;

    FILE *fptr;

    char * file;

    switch (argc) {
        case 2:
            host = argv[1];
            port = SERVER_TCP_PORT;
            filename = "medium.txt";
            break;
        case 3:
            host = argv[1];
            port = atoi(argv[2]);
            filename = "small.txt";
            break;
        case 4:
            host = argv[1];
            port = atoi(argv[2]);
            filename = argv[3];
            break;
        default:
            fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
            exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        printf("Error 01: could not create socket \n");

    bzero((char*)&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if ((hostp = gethostbyname(host)))
        bcopy(hostp->h_addr_list[0], (char *) &addr.sin_addr, hostp->h_length);
    else if (inet_aton(host, (struct in_addr *) &addr.sin_addr))
        printf("Error 02: could not resolve host id \n");


    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1)
        printf("Error 03: could not connect to server \n");

    if (sock > 0) {
        // request file
        strcpy(buffer, filename);
        write(sock, buffer, sizeof(buffer));

        bzero(buffer, BUFFER_LEN);

        n = read(sock, buffer, BUFFER_LEN); // read the size of the file

        if(strcmp(buffer, "error no file") == 0){
            printf("Error 04: file does not exist");
        }
        else {
            n = 0;
            int file_size = atoi(buffer);
            file = (char *) malloc(file_size + 10);
            chunks = ceil(file_size / PACKET_LEN);
            chunks += (file_size % PACKET_LEN) > 0 ? 1 : 0;

            while (n < file_size) {
                char temp[PACKET_LEN];
                int index = 0;
                index = read(sock, temp, PACKET_LEN);
                strcat(file, temp);
                n += index;
                bzero(temp, PACKET_LEN);
            }

            fptr = fopen(filename, "w");
            fwrite(file+6, 1, strlen(file)-6, fptr);
            fclose(fptr);
        }

    }

    close(sock);
    return 0;
}