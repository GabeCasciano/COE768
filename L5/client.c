#include "common.h"

#define HOST "127.0.0.1"
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
    int port = PORT, recv_len;
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

    pdu.data = (char *)malloc(PDU_DATA_LEN );
    buffer = (char *)malloc(PDU_DATA_LEN + 2);

    // get a file name
    printf("Enter a filename \n");
    scanf("%s", filename);

    strcpy(pdu.data, filename);

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
            file = (char *) malloc(atoi(pdu.data)); // this is causing a abrt

            // send ack
            sendAck(server);

            // recv until F
            while (pdu.type != PDU_TYPE_FINAL || pdu.type != PDU_TYPE_ERROR){

                buffer = (char *) realloc(buffer, PDU_DATA_LEN + 2);
                bzero(buffer, strlen(buffer));

                recv_len = read(server.sockfd, buffer, PDU_DATA_LEN + 2);
                pdu = unserialized(buffer, &pdu);

                if(pdu.type == PDU_TYPE_DATA){
                    strcat(file, pdu.data);
                    sendAck(server);


                }else { // error or final
                    if (file != NULL)
                        string_to_file(filename, file);
                    free(file);
                    break;
                }
            }
        }

    } else{

    }

    free(buffer);
    close(server.sockfd);


}