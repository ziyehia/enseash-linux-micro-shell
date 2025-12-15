#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils.h>

#define BUFSIZE 128

void welcome_prompt(void){
    myprint("Welcome to enseash!\n\rTo exit, type 'exit'\n\r");

}

void input_scan(void){

    myprint("enseash % ");

    char user_input[BUFSIZE];

    ssize_t n = myscan(user_input, BUFSIZE);

    if ( n == 0 ) {     // n = 0 means ctrl+D was pressed
        myprint("\nsee you soon ;)\n");
        exit(EXIT_SUCCESS);
    } 

    if ( strcmp(user_input, "exit\n") == 0) {    
        myprint("see you soon ;)\n");
        exit(EXIT_SUCCESS);
    } 
    
    else {
        myprint("invalid command\n");
    }
}