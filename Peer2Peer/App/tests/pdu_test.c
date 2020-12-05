//
// Created by gabe on 2020-12-05.
//

#include "../common.h"

int main(){


    printf("Running files test \n");
    system("./File_test");

    char * file = (char *)malloc(256);
    char * buff = (char*)malloc(256);

    printf("Reading file from text \n");

    read_file("testfile1.txt", file, filesize("testfile1.txt"));

    struct pdu_t pdu = init_pdu(PDU_CONTENT, file);

    if(strlen(pdu.data) == strlen(file))
        printf("sucessful copy\n");
    else
        printf("not sucessful copy\n");



    printf("Serialized: %s \n", serialized(pdu, buff));

    unserialized(buff, &pdu);

    if(pdu.type == PDU_CONTENT)
        printf("good uncereal");
    else
        printf("not good");

    return 0;
}