//
// Created by gabe on 2020-12-05.
//

#include "../common.h"

void function(int * running){
    while (running ){
        printf("running");
    }
    exit(0);
}


int main(){

    int * running;
    int on = 1;
    int off = 0;
    *running = &on;
    int counter = 1000;
    int pid;

//    if((pid = fork()) == 0){ //child
//        for(int i = counter; i > 0; i--){
//            printf("main loop");
//        }
//        *running = &off;
//        exit(0);
//    }
//    else{
//
//        function(running);
//    }

    return 0;
}