#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils.h>

#define BUFSIZE 128

void welcome_prompt(void){
    myprint("Welcome to enseash!\n\r");

}

void exit_scan(void){
    myprint("To exit, type 'exit'\n\r");
    char user_input[BUFSIZE];
    char *input = myscan();

     if (!input)
        return;

    strcpy(user_input, input);
    free(input);

    if (strcmp(user_input, "exit\n") == 0 ||
        strcmp(user_input, "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        myprint("invalid command\n");
    }
}