//
// Created by gabe on 2020-12-05.
//

#include "common.h"
#include <pthread.h>
#include <signal.h>

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
            int running = 0;

            pid_t child;
            //pthread_t server;

            //pthread_create(&server, NULL, download_server , (void *)&running);
            do_registration();

            child = fork();
            if(child == 0)
            {
                download_server();

                exit(0);
            }
            else if(child > 0){
                download_client();
                kill(child, SIGKILL);
                do_unregistration();

            }
            else
                printf("it got fucked");



            //pthread_join(server, NULL);

            printf("goodbye");
        }
    }

    return 0;

}