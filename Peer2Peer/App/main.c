//
// Created by gabe on 2020-11-18.
//

#include "Index_Server.h"
#include "Client.h"

#define CMD_SERVER "-s"
#define CMD_CLIENT "-c"

int main(int argc, char ** argv){
    int application_type = 0;
    int running = 1;

    if(argc > 1){
        if(strcmp(argv[1], CMD_SERVER) == 0 ){
            application_type = 1;
        }
        else if(strcmp(argv[1], CMD_CLIENT) == 0){
            application_type = 2;
        }
    }
    if(application_type == 1){
        struct server_parameters parameters;
        parameters.port = DEFAULT_PORT;
        parameters.num_clients = 2;
        index_server(parameters);
    }
    else{
        struct client_parameters parameters;
        parameters.port = DEFAULT_PORT;
        parameters.host = DEFAULT_ADDR;
        download_client(parameters);
    }

    /*if (application_type == 1) {
        // start the server task
        struct server_parameters params;
        params.port = DEFAULT_PORT;
        test_server(running, params);
    }
    else{
        struct client_parameters params;
        params.port = DEFAULT_PORT;
        params.host = DEFAULT_ADDR;
        test_client(running, params);
    }*/
    return 0;
}