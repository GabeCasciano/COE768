//
// Created by gabe on 2020-11-26.
//

int running = 0;

int main(int argc, char ** argv){

    int application_type = 0;

    if(argc == 2){
        if(strcmp(argv[1], CMD_SERVER) ){
            application_type = 1;
        }
        else if(strcmp(argv[1], CMD_CLIENT)){
            application_type = 2;
        }
    }

    if (application_type == 1) {
        // start the server task
        index_server(&running);
    }
    else if(application_type == 2){
        // start the client task
        pid_t server_pid;
        if(server_pid = fork() == 0) {
            content_server(&running);
            exit(0);
        }
        else
            download_client(&running);

        wait(NULL);
    }

    return 0;
}