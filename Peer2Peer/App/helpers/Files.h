//
// Created by gabe on 2020-12-05.
//

#ifndef PEER2PEER_FILES_H
#define PEER2PEER_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_FILENAME_LEN 25
#define MAX_DIR_SIZE 10

struct cwd_t{
    int num_files;
    char ** files;
};

int filesize(char * filename){
    char _filename[strlen(filename)];
    char cwd[256];
    struct stat st;

    bzero(&_filename, strlen(filename));
    bzero(&cwd, 256);

    strcpy(&_filename, filename);
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/downloads/");
    strcat(cwd, _filename);

    if(stat(cwd, &st) != -1)
        return st.st_blksize;
    return -1;

}

void write_file(char * filename, char * data){
    char * filename_ = (char *)malloc(100);
    strcpy(filename_, "downloads/");
    strcat(filename_, filename);
    FILE * fptr = fopen(filename_, "w");
    if(fptr != NULL)
        fprintf(fptr, "%s", data);
    fclose(fptr);

}

char * read_file(char * filename, char * dest, int size){
    char * cwd = (char *)malloc(256);
    FILE * fptr;

    sprintf(cwd, "downloads/");

    strcat(cwd, filename);
    int file_size = filesize(filename);

    fptr = fopen(cwd, "r");
    if(fptr != NULL) {
        fread(dest, 1, size, fptr);
        fclose(fptr);
    }

    return dest;
}

struct cwd_t read_cwd(){
    struct dirent *de;
    DIR *dr = opendir("downloads");

    struct cwd_t directory;
    directory.num_files = 0;
    directory.files = (char**)malloc(MAX_DIR_SIZE);

    if(dr != NULL){
        while((de = readdir(dr))!= NULL) {
            if(directory.num_files < MAX_DIR_SIZE) {
                if (strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0) {
                    directory.files[directory.num_files ] = (char *) malloc((MAX_FILENAME_LEN));
                    strncpy(directory.files[directory.num_files ], de->d_name, MAX_FILENAME_LEN);
                    directory.num_files++;
                }
            }
        }
    }
    return directory;
}

int file_in_cwd(char * filename){
    struct cwd_t directory = read_cwd();

    for(int i = 0; i < directory.num_files; i++){
        if(filename != NULL) {
            if (strcmp(directory.files[i], filename) == 0) {
                free(directory.files);
                return i;
            }
        }
    }

    free(directory.files);
    return -1;
}

#endif //PEER2PEER_FILES_H
