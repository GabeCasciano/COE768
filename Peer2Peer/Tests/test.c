//
// Created by gabe on 2020-11-19.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>

int running = 1;

void *thread_1(void * ptr){
    int counter = 0;
    while(counter < 100) {
        printf("Hell from thread 1, %d \n", counter);
        counter++;
    }
    exit(1);
}

void *thread_2(void * ptr){
    int counter = 0;
    while(counter < 100) {
        printf("Hell from thread 2, %d \n", counter);
        counter++;
    }
    exit(1);
}

int main(){
    printf("Hello from the start of main \n");

    while (running){
        int p1 = fork();
        if(p1 == 0){
            thread_1(NULL);
        }
        int p2 = fork();
        if(p2 == 0){
            thread_2(NULL);
        }

        wait(NULL);
        running = 0;
    }

    /*
    pthread_t th1, th2;

    pthread_create(&th1, NULL, thread_1, NULL);
    pthread_create(&th2, NULL, thread_2, NULL);

    printf("Hello from after the threads \n");

    sleep(.1);
    running = 0;

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("Hello from threads completed \n");
    */

    return 0;

}