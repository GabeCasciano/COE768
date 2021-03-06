#include "common.h"

#define HOST "3.21.129.10"
#define PORT 8080

void sendAck(struct sock_t server){
    char buff[PDU_DATA_LEN + 2];
    struct pdu_t pdu;

    pdu.data = "";
    pdu.type = PDU_TYPE_ACK;

    bzero(pdu.data, strlen(pdu.data));

    serialized(pdu, buff);
    write(server.sockfd, buff, strlen(buff));
}

int main(int argc, char** argv){

    struct sock_t server;
    struct pdu_t pdu;
    int port = PORT, recv_len, run = 1;
    char * host = HOST;
    char * buffer, * file;
    char filename[50];

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

    pdu.data = malloc(PDU_DATA_LEN);
    buffer = malloc(PDU_DATA_LEN + 2);

    while (run) {
        // get a file name
        printf("Enter a filename \n");
        scanf("%s", filename);

        strcpy(pdu.data, filename);

        if (pdu.data != NULL && strcmp(pdu.data, "exit") >= 1) {
            // request file from server
            pdu.type = PDU_TYPE_FILENAME;
            server = init_client(host, port);
            buffer = serialized(pdu, buffer);

            write(server.sockfd, buffer, strlen(buffer));

            // get filesize
            bzero(buffer, PDU_DATA_LEN + 2);
            recv_len = read(server.sockfd, buffer, PDU_DATA_LEN + 2);
            //recv_len = recvfrom(server.sockfd, buffer, PDU_DATA_LEN + 2, 0, (struct sockaddr *)&server.sockaddr, &server.sockaddr_len);
            pdu = unserialized(buffer, &pdu);

            if (pdu.type == PDU_TYPE_FILENAME) {
                // prepare location
                file = malloc(atoi(pdu.data)); // this is causing a abrt

                // send ack
                sendAck(server);

                // recv until F
                do{
                    bzero(buffer, PDU_DATA_LEN+2);

                    recv_len = read(server.sockfd, buffer, PDU_DATA_LEN + 2);
                    pdu = unserialized(buffer, &pdu);

                    if (pdu.type == PDU_TYPE_DATA) {
                        strcat(file, pdu.data);
                        sendAck(server);

                    } else if(pdu.data == PDU_TYPE_FINAL){ // error or final
                        if (file != NULL)
                            string_to_file(&filename, file);
                        break;
                    }
                }while (pdu.type != PDU_TYPE_ERROR);
            }
            if(file != NULL)
                free(file);
            close(server.sockfd);

        } else
            run = 0;
    }

    free(buffer);
    free(pdu.data);
    return 0;

}