#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"

#define BUFSIZE 128

void myprint(const char *s){
    if(write(STDOUT_FILENO, s, strlen(s)) == -1){
        perror("write");
        exit(EXIT_FAILURE);
    }
}

char *myscan(void){ 
    size_t nbytes = BUFSIZE;
    char *buff[nbytes];
    if((read(STDOUT_FILENO, buff, nbytes)) == -1){
        perror("read");
    }

    return *buff;
}

