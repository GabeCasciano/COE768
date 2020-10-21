//
// Created by gabe on 2020-10-21.
//

#include "../common.h"
#include <stdio.h>

int main(){

    char string[] = "hello my name is gabriel M casciano, this string needs to be more than 100 characters long for me to be sure that my function is actually working correctly, I hope that this is string is nearly long enough";
    struct packed_t packets;

    packets = strpack(string, strlen(string));

    printf("%d\n", packets.num_packets);


}