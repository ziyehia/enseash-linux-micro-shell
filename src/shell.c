#include "config.h"
#include <linux/limits.h>

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

    if (user_input[0] == '\0') {
        myprint("You pressed Enter with nothing :P \n");
        myprint("enseash % "); 
        return;
    }


    
    else {

        char *token = " ";  
        char *argv[ARG_MAX]; 
        string_split(user_input, token, argv);



        // treating redirection with > 
        char *output_file = NULL;

        for (int i = 0; argv[i] != NULL; i++) {
            if (strcmp(argv[i], ">") == 0) {
    
                if (argv[i+1] != NULL) {
                    output_file = argv[i+1];
                } else {
                    myprint("Error: No file specified after >\n");
                    return; 
                }

                argv[i] = NULL; 
                
                break; 
            }
        }

        // end of treatment


        // params to calculate executation time
        struct timespec start, end;
        long exec_time_ms;                                               // struct timespec contains long values

        clock_gettime(CLOCK_MONOTONIC, &start);

        int status = command_exec(argv[0], argv, output_file);

        clock_gettime(CLOCK_MONOTONIC, &end);

        exec_time_ms = timespec_diff_ms(&start, &end);                   
        char time_ms_buf[TIME_BUFSIZE];
        itoa_long(exec_time_ms, time_ms_buf);                            // for itoa_long(), check utils.c
        

        // console output
        myprint("enseash ");
        if (WIFEXITED(status)) {
            char buffer[ERR_SIG_BUFSIZE];
            itoa(WEXITSTATUS(status), buffer);                           // for itoa(), check utils.c

            myprint("[exit:");
            myprint(buffer);    
            myprint("|");    
            myprint(time_ms_buf);
            myprint("ms]");   
        }
        else if ((WIFSIGNALED(status))) {
            char buffer[ERR_SIG_BUFSIZE];
            itoa(WTERMSIG(status), buffer);
            
            myprint("[sign:");
            myprint(buffer);    
            myprint("|");    
            myprint(time_ms_buf);
            myprint("ms]");    
        }
        myprint(" % ");
    }


}