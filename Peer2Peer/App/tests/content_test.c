//
// Created by gabe on 2020-12-05.
//

#include "../common.h"

int main(){

    struct content_t content[5];
    int port1 = 1234;
    int port2 = 1235;
    char * addr1 = "0.0.0.0";
    char * addr2 = "1.1.1.1";

    char * file1 = "filename1";
    char * file2 = "filename2";

    printf("Starting content test \n");

    content[0] = init_content(port1, addr1);
    content[1] = init_content(port2, addr2);

    printf("init 2 content locations \n");

    add_content(&content[0], file1);
    add_content(&content[0], file2);

    printf("added 2 files to content 0 \n");

    if(content[0].num_files = 2)
        printf("corrent num of files \n");
    else
        printf("incorrent num of files \n");

    if(strcmp(content[0].files[0], file1) == 0)
        printf("corrent files in 0 \n");
    else
        printf("incorrent file in 0 \n");

    if(strcmp(content[0].files[1], file2) == 0)
        printf("corrent files in 1 \n");
    else
        printf("incorrent file in 1 \n");

    remove_content(&content[0], file1);

    printf("removed 1 files to content 0 \n");

    if(content[0].num_files = 1)
        printf("corrent num of files \n");
    else
        printf("incorrent num of files \n");

    if(strcmp(content[0].files[0], file2) == 0)
        printf("corrent files in 0 \n");
    else
        printf("incorrent file in 0 \n");
}
