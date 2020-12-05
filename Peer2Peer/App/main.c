//
// Created by gabe on 2020-12-05.
//

#include "common.h"

#define STRT_CMD_SERV   "-s"
#define STRT_CMD_CLI    "-c"
#define STRT_CMD_DSERV  "-d"

int main(int argc, char * argv[]){

    if(argc > 1){
        if (strcmp(argv[1], STRT_CMD_SERV)==0){
            // start the index server
            printf("Starting index server \n");
            index_server();
        }
        else if(strcmp(argv[1], STRT_CMD_CLI)==0){
            // start the d client
            download_client();
        }
        else if(strcmp(argv[1], STRT_CMD_DSERV)==0){
            // start the d server
            download_server();
        }
    }

    return 0;

}