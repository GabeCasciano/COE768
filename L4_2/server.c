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
#include <math.h>
#include <sys/stat.h>

#define SERVER_TCP_PORT 8080	/* well-known port */
#define BUFLEN		256	/* buffer length */
#define PACKET_LEN 100

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

int main(){
    int server_socket, client_socket, running = 1, n;
    struct sockaddr_in server_addr, client_addr;
    char buf[BUFLEN], *file, filename[256];
    FILE *fptr;



    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        printf("Error 01: could not create socket \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_TCP_PORT);

    if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        printf("Error 02: could not bind server \n");

    if(listen(server_socket, 5) < 0)
        printf("Error 03: could not listen to port \n");

    while (running) {
        client_socket = accept(server_socket, (struct sockaddr *) NULL, (socklen_t *) NULL);
        if (client_socket < 0)
            printf("Error 04: could not accept new client. %d \n", client_socket);

        n = read(client_socket, buf, BUFLEN);

        bzero(filename, 256);
        getcwd(filename, sizeof(filename));
        strcat(filename, "/tmp/");
        strcat(filename, buf);

        fptr = fopen(filename, "r");
        if(fptr != NULL) {
            int file_size = fsize(fptr);
            int chunks = file_size / PACKET_LEN;
            chunks += (file_size % PACKET_LEN) > 0 ? 1 : 0;
            
            file = (char *) malloc(file_size);
            bzero(file, file_size);
            bzero(buf, BUFLEN);
            sprintf(buf, "%d", file_size);

            write(client_socket, buf, sizeof(buf)); // tell client the size of the file

            fread(file, 1, file_size, fptr); // read the file
            fclose(fptr);

            int index = 0;
            for (int i = 0; i < chunks; i++) {
                char temp[PACKET_LEN];
                strncpy(temp, file + index, file_size - index);
                index += PACKET_LEN;
                write(client_socket, temp, sizeof(temp)); // send the file to the client

                bzero(temp, PACKET_LEN);
            }
            running = 0;
        }
        else{
            bzero(buf, BUFLEN);
            strcpy(buf, "error no file");
            write(client_socket, buf, sizeof(buf));
            running = 0;
        }
        close(client_socket);
    }
    
    close(server_socket);
    return 0;

}
