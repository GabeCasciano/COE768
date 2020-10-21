#include "common.h"

#define PORT 8080

void send_error(struct sock_t server, struct sock_t client, struct pdu_t pdu){
    char * buffer;
    buffer = (char *)malloc(PDU_DATA_LEN + 2);
    pdu.type = PDU_TYPE_ERROR;
    buffer = serialized(pdu, buffer);
    sendto(server.sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client.sockaddr, client.sockaddr_len);
    free(buffer);
}

void send_final(struct sock_t server, struct sock_t client){
    struct pdu_t pdu;
    char * buffer;
    buffer = (char *)malloc(PDU_DATA_LEN + 2);
    pdu.type = PDU_TYPE_FINAL;
    buffer = serialized(pdu, buffer);
    sendto(server.sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client.sockaddr, client.sockaddr_len);

    free(buffer);
}

int main(int argc, char** argv){


    struct sock_t server, client;
    struct pdu_t pdu;
    struct packed_t packet;
    int port = PORT, run = 1, recv_len;
    char * buffer;

    switch (argc) {
        case 2:
            port = atoi(argv[1]);
            break;
    }

    server = init_server(port);
    client.sockaddr_len = sizeof(client.sockaddr);
    pdu.data = (char *)malloc(PDU_DATA_LEN + 2);

    buffer = (char *)malloc(PDU_DATA_LEN + 2);
    recv_len = recvfrom(server.sockfd, buffer, PDU_DATA_LEN + 2, 0, (struct sockaddr *)&client.sockaddr, &client.sockaddr_len);
    pdu = unserialized(buffer, &pdu);

    if(pdu.type == PDU_TYPE_FILENAME){
        // get filesize
        char * filename;
        char * file;

        filename = (char *)malloc(strlen(pdu.data));

        strcpy(filename, pdu.data);
        bzero(pdu.data, strlen(pdu.data));

        if(filesize(filename) > 0) { // check if file actually exists
            sprintf(pdu.data, "%d", filesize(filename));
            // send filesize
            buffer = serialized(pdu, buffer);
            sendto(server.sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &client.sockaddr, client.sockaddr_len);

            // wait for ack
            buffer = (char *) realloc(buffer, PDU_DATA_LEN + 2);
            bzero(buffer, strlen(buffer));
            recv_len = recvfrom(server.sockfd, buffer, PDU_DATA_LEN + 2, 0, (struct sockaddr *) &client.sockaddr, &client.sockaddr_len);
            pdu = unserialized(buffer, &pdu);

            if (pdu.type != PDU_TYPE_ACK) { // error
                bzero(pdu.data, strlen(pdu.data));
                send_error(server, client, pdu);

            } else { // recv'd ack from client

                // pack
                file = (char *)malloc(filesize(filename));
                file = file_to_string(filename, file, filesize(filename));
                packet = strpack(file, strlen(file));

                // send file
                for (int i = 0; i < packet.num_packets; i++) {
                    buffer = serialized(packet.pdu[i], buffer);
                    sendto(server.sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &client.sockaddr,
                           client.sockaddr_len);

                    buffer = (char *) realloc(buffer, PDU_DATA_LEN + 2);
                    bzero(buffer, strlen(buffer));
                    recv_len = recvfrom(server.sockfd, buffer, PDU_DATA_LEN + 2, 0, (struct sockaddr *) &client.sockaddr, &client.sockaddr_len);
                    pdu = unserialized(buffer, &pdu);

                    if (pdu.type != PDU_TYPE_ACK) { // error
                        pdu.type = PDU_TYPE_FINAL;
                        bzero(pdu.data, strlen(pdu.data));
                        send_error(server, client, pdu);
                        break;
                    }
                }
            }
        } else{
            send_error(server, client, pdu);
        }

        //send final
        send_final(server, client);
        free(filename);
        free(file);

    } else{ // send error and close connection
       send_error(server, client, pdu);
    }

    free(buffer);
    close(server.sockfd);
    return 0;

}