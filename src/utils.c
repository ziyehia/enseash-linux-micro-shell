#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
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

ssize_t myscan(char *buff, size_t size){ 

    ssize_t n = read(STDIN_FILENO, buff, size);

    if(n == -1){
        perror("read");
        return -1;
    }

    buff[n] = '\0';                            //required for a working strcmp
    return n;
}

void command_no_arg_exec(const char *file, const char *arg0){
    
    int pid, status;
    pid = fork();

    if (pid != 0){                                 //parent code
        wait(&status);
    } else {                                       //child code
        execlp(file, arg0, (char *)NULL);
        perror(file);
        exit(EXIT_SUCCESS);
    }

}