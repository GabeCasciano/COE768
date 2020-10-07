// Gabriel Casciano, 500744076
// Tcp socket server for COE768 L3

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

// Constants
#define SERVER_TCP_DEF_PORT 8080
#define BUFFER_LEN 256
#define NUM_THREADS 4

struct session_data{
    uint8_t thread_id;
    uint8_t alive;
    uint8_t status;
    int socket;
    char BUFFER[BUFFER_LEN];
    struct sockaddr_in addr;
};

struct session_data session_data_array[NUM_THREADS];
pthread_mutex_t printf_mutex;

int status = 0;

void *session(void *threadarg);
void *session_master(void *threadarg);


int main(int argc, char **argv) {
    // -- Variables
    pthread_t master;

    if(pthread_create(&master, NULL, session_master, (void*)1)){
        printf("Failed to create master \n");
        exit(EXIT_FAILURE);
    }

    while(status = 0){
        if(pthread_mutex_trylock(&printf_mutex)){
            printf("Enter a command: \n");
            int com = (int)getchar();

            if(com == 1){
                status = -1;
            }
            else{
                status = 0;
            }
        }

    }

    pthread_join(master, NULL);
    pthread_exit(NULL);
}


void *session_master(void *threadarg){

    // thread vars
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&printf_mutex, NULL);

    // socket vars
    int server_sock, new_sock;
    struct sockaddr_in addr, client;

    // Create a socket to host the server with
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Initialize the address structure
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(SERVER_TCP_DEF_PORT);


    // Bind socket to port
    if(bind(server_sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
        printf("Failed to bind to port\n");
        exit(EXIT_FAILURE);
    }

    if(listen(server_sock, NUM_THREADS) < 0){
        printf("Failed to listen to port\n");
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < NUM_THREADS; i++){
        session_data_array[i].thread_id = i;
        session_data_array[i].alive = 1;
        session_data_array[i].status = 0;
    }

    while (status != -1){
        new_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*) sizeof(client));

        if(new_sock < 0){
            printf("Failed to accept new socket\n");
        }else{
            for(int i = 0; i < NUM_THREADS; i++){
                if(!session_data_array[i].status  && !session_data_array[i].alive == 0){
                    session_data_array[i].socket = new_sock;
                    session_data_array[i].addr = client;
                    session_data_array[i].status = 1;
                    session_data_array[i].alive = 1;
                    if(pthread_create(&threads[i], NULL, session, (void *) &session_data_array[i]) < 0){
                        printf("error creating thread %d \n",i);
                    }

                }
            }
        }

    }



    // Exit routine below
    for(int i = 0; i < NUM_THREADS; i++){
        session_data_array[i].alive = -1;
    }

    for(int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    close(server_sock);
    pthread_mutex_destroy(&printf_mutex);

}

void *session(void *threadarg){

    struct session_data *my_data;
    my_data = (struct session_data *) threadarg;
    uint8_t taskid = my_data->thread_id;

    do{
        if(my_data->status == 1 && read(my_data->socket, my_data->BUFFER, BUFFER_LEN) < 0) {
            if (pthread_mutex_trylock(&printf_mutex))
                printf("Session ID: %d, message: %s", my_data->thread_id, my_data->BUFFER);
            my_data->status = 2;
        }
        else
            fprintf(stderr, "Socket read error on thread %d \n", my_data->thread_id);

        if(my_data->status == 2){
            write(my_data->socket, my_data->BUFFER, sizeof(my_data->BUFFER));
            my_data->status = 1;
        }

    }while(my_data->alive != -1);

    my_data->status = 0;
    my_data->alive = 0;
    close(my_data->socket);
    pthread_exit(NULL);
}