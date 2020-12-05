//
// Created by gabe on 2020-12-05.
//

#ifndef PEER2PEER_CONTENT_H
#define PEER2PEER_CONTENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILENAME_LEN 25
#define MAX_FILES_PER_CONTENT 10

struct content_t{
    int port;
    char * addr;
    int num_files;
    char ** files;
};

struct content_t init_content(int port, char * addr){
    struct content_t content;

    content.port = port;
    content.addr = (char *)malloc(20);
    strcpy(content.addr, addr);
    content.num_files = 0;

    content.files = (char **)malloc(MAX_FILES_PER_CONTENT);

    return content;
}

void add_content(struct content_t * content, char * filename){

    content->files[content->num_files] = (char *)malloc(MAX_FILENAME_LEN);
    strcpy(content->files[content->num_files], filename);
    content->num_files++;
}

int contains_content(struct content_t * content, char * filename){
    for(int i = 0; i < content->num_files; i++){
        if(strcmp(content->files[i], filename) == 0)
            return i;
    }
    return  -1;
}

int remove_content(struct content_t * content, char * filename){
    int location = contains_content(content, filename);

    if(location != -1) {
        content->num_files--;
        if (location != content->num_files) { // file to be deleted is not the last file
            memcpy(content->files[location], content->files[content->num_files],
                   strlen(content->files[content->num_files])); // remove the item by replacing it with the last item

        }
        bzero(content->files[content->num_files],
              strlen(content->files[content->num_files])); // remove the last file (it has been copied to a new location)

        // This is going to memory leak for sure, need to reduce the list after

        return 1;
    }
    return -1;
}



int find_server_with_file(struct content_t * content, int len, char * filename){
    for(int i = 0; i < len; i++){
        if(content[i].num_files != 0) {
            if(contains_content(&content[i], filename) >= 0)
                return i;
        }
    }
    return -1;
}

int find_server_with_addr(struct content_t * content, int len, char * addr){
    for(int i = 0; i < len; i++){
        if(content->addr != NULL) {
            if (strcmp(content->addr, addr) == 0) {
                return i;
            }
        }
    }
    return -1;
}


#endif //PEER2PEER_CONTENT_H
