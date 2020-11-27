g// Gabriel Casciano, 500744076, L4
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
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "headers.h"
#include "networking.h"

#define SERVER_TCP_PORT 8080	/* well-known port */
#define BUFLEN		256	/* buffer length */


int main(int argc, char **argv) {
    int sock, port;
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

    //init_client(&sock, &server, port, hp, host);



    return 0;
}
