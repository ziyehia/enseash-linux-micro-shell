#include "config.h"

void myprint(const char *s){
/* write a null-terminated string to STDOUT using write() */

    if(write(STDOUT_FILENO, s, strlen(s)) == -1){
        perror("write");
        exit(EXIT_FAILURE);
    }
}

ssize_t myscan(char *buff, size_t size){ 
/* read user input from STDIN and null-terminate the buffer */

    ssize_t n = read(STDIN_FILENO, buff, size - 1);

    if(n == -1){
        perror("read");
        return -1;
    }

    buff[n] = '\0';                                //required for a working strcmp
    return n;
}

int command_no_arg_exec(const char *file, const char *arg0){

    int pid, status;
    pid = fork();

    if (pid != 0){                                 //parent code
        wait(&status);

    } else {                                       //child code
        execlp(file, arg0, (char *)NULL);
        perror(file);
        exit(EXIT_FAILURE);
    }

    return status;

}

long timespec_diff_ms(struct timespec *start, struct timespec *end){
    
    long seconds = end->tv_sec - start->tv_sec; 
    long nanoseconds = end->tv_nsec - start->tv_nsec;

    // treatment of negative difference case
    // analog to standard manual difference calculation of real integers
    if (nanoseconds<0){
        seconds--;
        nanoseconds += 1000000000;                                    // = 1 second in nanoseconds
    }

    long total_ms = (seconds * 1000) + (nanoseconds / 1000000);

    return total_ms;

}

void string_split(char s[], char *argv[]){
/* split a command string into argv-compatible tokens*/

    int i = 0;
    char *token;

    token = strtok(s, " ");
    
    while (token != NULL && i < ARG_MAX - 1) {
        argv[i] = token; 
        i++;
        token = strtok(NULL, " ");                            // isolate a word when space is detected
    }

    argv[i] = NULL;                                          // add NULL at the end so it's compatible with execvp

}


int command_exec(const char *file, char *argv[], char *input_file, char *output_file){
/* execute a command with arguments and optional I/O redirection */

    int pid, status;
    pid = fork();

    if (pid != 0){                                 //parent code
        wait(&status);

    } else {                                       //child code


    // redirection if input file precised
        if (input_file != NULL) {
            int fd_in = open(input_file, O_RDONLY);
            if ( fd_in == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            if (dup2(fd_in, STDIN_FILENO) == -1) {                     //copies fd_in on STDIN_FILENO  and closes STDIN_FILENO
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fd_in);


        }

    // redirection if output file precised
        if (output_file != NULL) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);     // write only, create if does not exist, delete old file content, make file private, read and write perms for user only 
            if (fd_out == -1) {
                perror("open"); 
                exit(EXIT_FAILURE);
            }

            if (dup2(fd_out, STDOUT_FILENO) == -1) {                     
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fd_out);
        }
 

    // command execution 
        execvp(file, argv);
        perror(file);
        exit(EXIT_FAILURE);
    }

    return status;

}



/* Comment from Author : this section is to implement the itoa() non standard function */
/* itoa:  convert n to characters in s */
/* The code is taken from Kernighan and Ritchie's The C Programming Language - 2nd edition */

/* reverse:  reverse string s in place */
void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

/* itoa() for long conversion function*/
/* adapted by Author*/
void itoa_long(long n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  