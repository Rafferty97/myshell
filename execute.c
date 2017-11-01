/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int execute_shellcmd(SHELLCMD *t)
{
    return exec_shellcmd(t, stdin, stdout);
}
