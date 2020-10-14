//
// Created by gabriel on 2020-10-14.
//


#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <math.h>

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

int main(){
    FILE *fptr;
    char name[256];
    char *tmp;



    getcwd(name, sizeof(name));

    strcat(name, "/tmp/small.txt");

    printf("%s\n", name);

    fptr = fopen(name, "r");
    printf("file open\n");
    tmp = (char *)malloc(256);
    fread(tmp, 1, 256, fptr);
    printf("%s",tmp);
    

}