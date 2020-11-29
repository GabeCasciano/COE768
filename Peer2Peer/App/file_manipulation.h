//
// Created by gabe on 2020-11-28.
//

#ifndef PEER2PEER_FILE_MANIPULATION_H
#define PEER2PEER_FILE_MANIPULATION_H

#include "common.h"
#include <dirent.h>

#define MAX_FILENAME_LEN 25
#define MAX_DIR_SIZE 25

// -- Content Data structures --

struct content_t{
    int port;
    char * addr;
    int num_files;
    char ** files;
};

struct content_t init_content(int port, char * addr){
    struct content_t content;

    content.port = port;
    content.addr = (char *)malloc(sizeof(addr));
    strcpy(content.addr, addr);
    content.num_files = 0;

    return content;
}

void add_content(struct content_t * content, char * filename){
    content->num_files++;

    if(content->num_files == 1)
        content->files = (char **) malloc(content->num_files);
    else
        content->files = (char **)realloc(content->files, content->num_files);

    content->files[content->num_files-1] = (char *)malloc(MAX_FILENAME_LEN);
    strcpy(content->files[content->num_files-1], filename);
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

        if (content->num_files == 0)
            free(content->files);

        return 1;
    }
    return -1;
}

// -- File manipulaton

int filesize(char * filename){
    char _filename[strlen(filename)];
    char cwd[256];
    struct stat st;

    bzero(&_filename, strlen(filename));
    bzero(&cwd, 256);

    strcpy(&_filename, filename);
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/tmp/");
    strcat(cwd, _filename);

    if(stat(cwd, &st) != -1)
        return st.st_blksize;
    return -1;

}

void read_file(char * filename, char * data){
    FILE * fptr = fopen(filename, "w");
    if(fptr != NULL)
        fprintf(fptr, "%s", data);
    fclose(fptr);

}

char * write_file(char * filename, char * dest, int size){
    char cwd[256];
    char _filename[strlen(filename)];
    FILE * fptr;

    bzero(&_filename, strlen(filename));
    bzero(&cwd, 256);
    bzero(dest, size);

    strcpy(&_filename, filename);
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/tmp/");
    strcat(cwd, _filename);

    fptr = fopen(cwd, "r");
    if(fptr != NULL)
        fread(dest, 1, size, fptr);

    fclose(fptr);
    return dest;
}

struct cwd_t{
    int num_files;
    char ** files;
};

struct cwd_t read_cwd(){
    struct dirent *de;
    DIR *dr = opendir(".");

    struct cwd_t directory;
    directory.num_files = 0;
    directory.files = (char**)malloc(MAX_DIR_SIZE);

    if(dr != NULL){
        while((de = readdir(dr)) != NULL) {
            directory.num_files++;
            if (strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0) {
                directory.files[directory.num_files - 1] = (char *) malloc((MAX_FILENAME_LEN));
                strncpy(directory.files[directory.num_files - 1], de->d_name, MAX_FILENAME_LEN);
            } else
                directory.num_files--;
        }
    }
    return directory;
}


int file_in_cwd(char * filename){
    struct cwd_t directory = read_cwd();

    for(int i = 0; i < directory.num_files; i++){
        if(strcmp(directory.files[i], filename) == 0){
            free(directory.files);
            return 1;
        }
    }

    free(directory.files);
    return -1;
}




#endif //PEER2PEER_FILE_MANIPULATION_H
