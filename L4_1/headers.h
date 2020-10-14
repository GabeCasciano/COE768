//
// Created by gabriel on 2020-10-13.
//

#ifndef L4_1_HEADERS_H
#define L4_1_HEADERS_H

#define MAX_LEN 128

#include <stdint.h>
#include <string.h>

struct file_header{
    /*
     * 1. .txt
     * 2. .html
     * 3. .png
     */
    uint8_t id;
    uint32_t size;
    char *name;
};

struct command_packet{
    /*
     * 1. send msg (both)
     * 2. req file (both)
     * 3. send'ing file (cli -> server)
     * 4. recv'ing file (server -> cli)
     * 5. recv complete (both)
     * 66. close connection (client)
     */
    uint8_t id;
    char *data;
};



struct command_packet command_pack(uint8_t id, char data[]){
    struct command_packet new_packet;
    new_packet.id = id;
    new_packet.data = (char*)malloc(strlen(data));
    strcpy(&new_packet.data, &data);

    return new_packet;
}

struct file_header file_header_pack(uint8_t id, uint32_t size, char file_name[]){
    struct file_header new_header;
    new_header.id = id;
    new_header.size = size;
    new_header.name = (char*)malloc(strlen(file_name));
    strcpy(&new_header.name, &file_name);
    return new_header;

}

struct command_packet command_from_serial(char buf[]){
    char *tokens[2];
    struct command_packet new_packet;

    tokens[0] = strsep(&buf, ",");
    strcpy(&tokens[1], &buf);

    new_packet = command_pack(atoi(tokens[0]), tokens[1]);
    return new_packet;
}

char* command_to_serial(struct command_packet command){
    char *new_str = (char*)malloc(MAX_LEN);
    if(sizeof(command)>0){
        sprintf(new_str, "%d,%s", command.id, command.data);
    }
    return new_str;
}

struct file_header file_header_from_serial(char buf[]){
    char *tokens[3];
    struct file_header new_header;

    tokens[0] = strsep(&buf, ",");
    tokens[1] = strsep(&buf, ",");
    strcpy(&tokens[2], &buf);

    new_header = file_header_pack(atoi(tokens[0]), atoi(tokens[1]), tokens[2]);

    return new_header;
}

char* file_header_to_serial(struct file_header header){
    char new_str = (char*)malloc(MAX_LEN);
    if(sizeof(header) > 0){
        sprintf(new_str, "%d,%d,%s", header.id, header.size, header.name);
    }
    return new_str;
}

#endif //L4_1_HEADERS_H
