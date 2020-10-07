//
// Created by gabriel on 2020-10-07.
//


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_TCP_DEF_PORT 8080
#define BUFFER_LEN 256

/*	echod program	*/
int echod(int sd)
{
    char	*bp, buf[BUFFER_LEN];
    int 	n, bytes_to_read;

    while(n = read(sd, buf, BUFFER_LEN))
        write(sd, buf, n);
    close(sd);

    return(0);
}

int main(int argc, char **argv)
{
    // socket vars
    int server_sock, new_sock;
    struct sockaddr_in addr, client;

    // Create a socket to host the server with
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Initialize the address structure
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(SERVER_TCP_DEF_PORT);


    // Bind socket to port
    if(bind(server_sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
        printf("Failed to bind to port\n");
        exit(EXIT_FAILURE);
    }

    if(listen(server_sock, 2) < 0){
        printf("Failed to listen to port\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        new_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t *) sizeof(client));
        if(new_sock < 0){
            printf("Issue accepting socket ");
        }
        switch (fork()){
            case 0:
                (void) close(server_sock);
                exit(echod(new_sock));
            case -1:
                printf("Error forking");
            default:
                (void) close(new_sock);
        }

    }


    return 0;
}
