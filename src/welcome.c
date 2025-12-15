#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils.h>

#define BUFSIZE 128

void welcome_prompt(void){
    myprint("Welcome to enseash!\n\r To exit, type 'exit'\n\r");

    char user_input[BUFSIZE];
    strcpy(myscan(), user_input);

    if (strcmp("exit", user_input) == 0){
        exit(EXIT_SUCCESS);
    }

    else {
        myprint("test");
    }
}