#include "config.h"

void welcome_prompt(void){
    myprint("Welcome to enseash!\nTo exit, type 'exit'\nenseash % ");

}

void input_scan(void){
    char user_input[BUFSIZE];
    char *argv[ARG_MAX];

    ssize_t n = myscan(user_input, BUFSIZE);
    if (n < 0) {
        myprint("read error\n");
        return;
    }

    user_input[strcspn(user_input, "\n")] = '\0';        // to remove the \n at the end of user input : necessary for correctly reading commands

    /* Ctrl+D */
    if ( n == 0 ) {                                                // n = 0 means ctrl+D was pressed
        myprint("\nsee you soon ;)\n");
        exit(EXIT_SUCCESS);
    } 

    string_split(user_input, argv);

    if (argv[0] == NULL) {
        myprint("You pressed Enter with nothing :P \n");
        myprint("enseash % "); 
        return;
    }

    if (strcmp(argv[0], "exit") == 0) {    
        myprint("see you soon ;)\n");
        exit(EXIT_SUCCESS);
    } 

    
    else {

        // I/O redirections
        char *input_file = NULL;
        char *output_file = NULL;

        for (int i = 0; argv[i] != NULL; i++) {

            // treating redirection with <
            if (strcmp(argv[i], "<") == 0) {
                if (argv[i+1] == NULL) {
                    myprint("Error: No file specified after <\n");
                    myprint("enseash % ");
                    return;
                }
                input_file = argv[i+1];  
                argv[i] = NULL;          
            }
               
            // treating redirection with >
            else if (strcmp(argv[i], ">") == 0) {
    
                if (argv[i+1] != NULL) {
                    output_file = argv[i+1];
                } else {
                    myprint("Error: No file specified after >\n");
                    myprint("enseash % ");
                    return; 
                }

                argv[i] = NULL; 
                
            
            }
        }

        // end I/O redirections


        // execution time measurement
        struct timespec start, end;
        long exec_time_ms;                                               // struct timespec contains long values

        clock_gettime(CLOCK_MONOTONIC, &start);

        int status = command_exec(argv[0], argv, input_file, output_file);

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