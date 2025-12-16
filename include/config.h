#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "utils.h"

#define BUFSIZE 128
#define ERR_SIG_BUFSIZE 4
#define TIME_BUFSIZE 32
#define ARG_MAX 512