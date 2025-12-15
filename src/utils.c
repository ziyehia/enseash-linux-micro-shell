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
    char *buff = malloc(BUFSIZE);
    
    if((read(STDIN_FILENO, buff, BUFSIZE)) == -1){
        perror("read");
        free(buff);
        return NULL;
    }

    return buff;
}

