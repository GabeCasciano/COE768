#include "common.h"

#define HOST "127.0.0.1"
#define PORT 8080

void sendAck(struct sock_t server){
    char * buffer;
    struct pdu_t pdu;
    buffer = (char *)malloc(PDU_DATA_LEN + 2);

    pdu.type = PDU_TYPE_ACK;
    bzero(pdu.data, strlen(pdu.data));
    bzero(buffer, strlen(buffer));
    buffer = serialized(pdu, buffer);
    write(server.sockfd, buffer, strlen(buffer));
}

int main(int argc, char** argv){

    struct sock_t server;
    struct pdu_t pdu;
    FILE * fptr;
    int port = PORT, recv_len;
    char * host = HOST;
    char * buffer, * file;

    switch (argc) {
        case 2:
            port = atoi(argv[1]);
            host = HOST;
            break;
        case 3:
            port = atoi(argv[1]);
            host = argv[2];
            break;
    }

    pdu.data = (char *)malloc(PDU_DATA_LEN + 2);
    buffer = (char *)malloc(strlen(pdu.data));

    // get a file name
    printf("Enter a filename \n");
    scanf("%s", pdu.data);

    if(pdu.data != NULL){
        // request file from server
        pdu.type = PDU_TYPE_FILENAME;
        server = init_client(host, port);
        buffer = serialized(pdu, buffer);

        write(server.sockfd, buffer, strlen(buffer));

        // get filesize
        bzero(buffer, 102);
        recv_len = read(server.sockfd, buffer, PDU_DATA_LEN +2 );
        //recv_len = recvfrom(server.sockfd, buffer, PDU_DATA_LEN + 2, 0, (struct sockaddr *)&server.sockaddr, &server.sockaddr_len);
        pdu = unserialized(buffer, &pdu);

        if(pdu.type == PDU_TYPE_FILENAME){
            // prepare location
            //file = (char *) malloc(atoi(pdu.data) + 1);

            // send ack
            sendAck(server);

            // recv until F
            while (pdu.type != PDU_TYPE_FINAL || pdu.type != PDU_TYPE_ERROR){

                buffer = (char *) realloc(buffer, PDU_DATA_LEN + 2);
                bzero(buffer, strlen(buffer));

                recv_len = read(server.sockfd, buffer, PDU_DATA_LEN + 2);
                pdu = unserialized(buffer, &pdu);

                if(pdu.type == PDU_TYPE_DATA){
                    strcat(file, buffer);
                    sendAck(server);

                }else // error or final
                    break;

            }

        }

    } else{

    }

    free(host);
    free(buffer);
    free(file);
    free(fptr);
    close(server.sockfd);


}