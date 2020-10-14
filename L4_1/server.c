// Gabriel Casciano, 500744076, L4
#include <stdint.h>

/*
 * Server process,
 * 1. Bind server to port
 * 2. Wait for client
 * 3. Recv client files request for the small file
 * 4. Put header together and send
 * 5. Send small file
 * 6. Repeat 3. -> 5. for medium and large files
 * 7. Wait for disconnect request
 * 8. close server
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "headers.h"
#include "networking.h"

#define SERVER_TCP_PORT 8080	/* well-known port */
#define BUFLEN		256	/* buffer length */





int main(){
    int server_socket, running = 1;
    struct sockaddr_in server_addr, client_addr;
    struct connection conn;
    int n;
    char buf[BUFLEN];
    struct command_packet r_command, s_command;
    struct file_header file_head;
    FILE *fptr;

    init_server(&server_socket, &server_addr, SERVER_TCP_PORT, 2);

    if(accept_new_conns(&server_socket, &conn) < 0){
        printf("Could not connect new conn");
        exit(-1);
    }
    while(running) {
        while (n = read(conn.sock, buf, BUFLEN));

        r_command = command_from_serial(buf);

        if (r_command.id == 1) { // send a message to the server
            s_command = command_pack(1, "hello from server");
            bzero(&buf, BUFLEN);
            *buf = command_to_serial(s_command);
            write(conn.sock, buf, sizeof(buf));

        } else if (r_command.id == 2) { // request a file header from the server

            int id;
            char *filename = "./dir/";
            struct stat s;

            if (strstr(r_command.data, ".txt"))
                id = 1;
            else if (strstr(r_command.data, ".html"))
                id = 2;
            else if (strstr(r_command.data, ".png"))
                id = 3;

            strcat(filename, r_command.data);
            stat(filename, &s);

            file_head = file_header_pack(id, s.st_size, filename);

            *buf = file_header_to_serial(file_head);
            write(conn.sock, buf, sizeof(buf));

        } else if (r_command.id == 3) { // recv file from client

        } else if (r_command.id == 4) { // sending file to client
            if((fptr = fopen(file_head.name, "r") ) == NULL){
                printf("Error, could not open file\n");
            }
            *buf = (char *)malloc(file_head.size);

            fread(&buf, file_head.size, 1, fptr);
            write(conn.sock, buf, sizeof(buf));



        } else if (r_command.id == 5) { // recv/send complete

        } else if (r_command.id == 66) { // close the connection to client

        } else {
            printf("Error, incorrect id\n");
            running = 0;
        }


        bzero(buf, BUFLEN);
    }
    return 0;
}