//
// Created by gabe on 2020-12-05.
//

#include "../common.h"

int main(){

    // write a file
    char * string1 = "Hello my name is gabriel casciano, this is a test file to be written into the downloads \n "
                     "directory, I am making it long on purpose";
    char * string1_control = "Hello my name is gabriel casciano, this is a test file to be written into the downloads \n "
                     "directory, I am making it long on purpose";

    char * buffer;

    char * filename = "testfile1.txt";

    printf("Variable created \n preparing file \n");

    write_file(filename, string1);
    printf("Wrote to file \n");

    // get filesize
    int size = filesize(filename);
    printf("got filesize, %d \n", size);

    if(size >= strlen(string1))
        printf("size is correct \n");
    else
        printf("size is incorrect \n");

    // read a file
    buffer = (char *)malloc(size);
    read_file(filename, buffer);
    printf("Read from file \n");

    if(strcmp(buffer, string1_control) == 0)
        printf("file is correct \n");
    else
        printf("file is incorrect \n");

    // read cwd
    struct cwd_t cwd = read_cwd();
    printf("got cwd \n");
    if(cwd.num_files >= 1)
        printf("num files is correct \n");
    else
        printf("num files is incorrect \n");

    // find file in cwd
    int file_in = file_in_cwd(filename);

    if(strcmp(cwd.files[file_in], filename) == 0)
        printf("found file in dir \n");
    else
        printf("did not find file\n");



}