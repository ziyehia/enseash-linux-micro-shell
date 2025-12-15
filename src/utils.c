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















/* Comment from Author (Yehia) : this section is to implement the itoa() non standard function */
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
