#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "utils.h"

#define BUFSIZE 128

void myprint(const char *s){
/* this is a simple print function to print in console*/

    if(write(STDOUT_FILENO, s, strlen(s)) == -1){
        perror("write");
        exit(EXIT_FAILURE);
    }
}

ssize_t myscan(char *buff, size_t size){ 
/* this is a simple scan function to scan user input in console, returns ssize_t n the output of the standard read function*/

    ssize_t n = read(STDIN_FILENO, buff, size);

    if(n == -1){
        perror("read");
        return -1;
    }

    buff[n] = '\0';                                //required for a working strcmp
    return n;
}

int command_no_arg_exec(const char *file, const char *arg0){
/* this function is to executes commands with no arguments in our custom shell in a child process*/

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