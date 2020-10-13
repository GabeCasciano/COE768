// Gabriel Casciano, 500744076, L4
/*
 * Client process,
 * 1. Connect to server
 * 2. Request the small file
 * 3. Recv the header for the small file
 * 4. Recv the small file
 * 5. Repeat 2. -> 4. for the medium and large files
 * 6. Request disconnect.
 */


#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

#define SERVER_TCP_PORT 8080	/* well-known port */
#define BUFLEN		256	/* buffer length */
#define HEADER_SIZE 64


void init_socket(int* sd, struct sockaddr_in * server, int port, struct hostent * hp,  char * host){
    /* Create a stream socket	*/
    if ((*sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Can't creat a socket\n");
        exit(1);
    }

    bzero((char *) &server, sizeof(struct sockaddr_in));
    server->sin_family = AF_INET;
    server->sin_port = htons(port);
    if (hp = gethostbyname(host))
        bcopy(hp->h_addr, (char *) &server->sin_addr, hp->h_length);
    else if (inet_aton(host, (struct in_addr *) &server->sin_addr)) {
        fprintf(stderr, "Can't get server's address\n");
        exit(1);
    }

    /* Connecting to the server */
    if (connect(*sd, (struct sockaddr *) &server, sizeof(server)) == -1) {
        fprintf(stderr, "Can't connect \n");
        exit(1);
    }
}


int main(int argc, char **argv) {
    int n, i, bytes_to_read;
    int sd, port;
    struct hostent *hp;
    struct sockaddr_in server;
    char *host, rbuf[BUFLEN], sbuf[BUFLEN];

    switch (argc) {
        case 2:
            host = argv[1];
            port = SERVER_TCP_PORT;
            break;
        case 3:
            host = argv[1];
            port = atoi(argv[2]);
            break;
        default:
            fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
            exit(1);
    }

    //init_socket(&sd, &server, port, hp, host);


   


    /*
    //request the small file
    strcpy(rbuf, command_to_serial(command_pack(1, "hello server")));
    write(sd, rbuf, sizeof(rbuf));

    read(sd, sbuf, BUFLEN);

*/







    return 0;
}