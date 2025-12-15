#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils.h>

#define BUFSIZE 128

void welcome_prompt(void){
    myprint("Welcome to enseash!\n\rTo exit, type 'exit'\n\renseash % ");

}

void input_scan(void){
    char user_input[BUFSIZE];

    ssize_t n = myscan(user_input, BUFSIZE);
    user_input[strcspn(user_input, "\n")] = '\0';        // to remove the \n at the end of user input : necessary for correctly reading commands

    if ( n == 0 ) {                                                // n = 0 means ctrl+D was pressed
        myprint("\nsee you soon ;)\n");
        exit(EXIT_SUCCESS);
    } 

    if ( strcmp(user_input, "exit") == 0) {    
        myprint("see you soon ;)\n");
        exit(EXIT_SUCCESS);
    } 


    
    else {
        int status = command_no_arg_exec(user_input, user_input);

        myprint("enseash ");
        if (WIFEXITED(status)) {
            char buffer[BUFSIZE];
            itoa(WEXITSTATUS(status), buffer);

            myprint("[exit:");
            myprint(buffer);    
            myprint("]");       
        }
        else if ((WIFSIGNALED(status))) {
            char buffer[BUFSIZE];
            itoa(WTERMSIG(status), buffer);
            
            myprint("[sign:");
            myprint(buffer);    
            myprint("]"); 
        }
        myprint(" % ");
    }


}