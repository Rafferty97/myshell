#include "myshell.h"
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
   CITS2002 Project 2 2017
   Name(s):		Alexander Rafferty, Dhaval Vaghjiani
   Student number(s):	21712241, 22258431
   Date:		03/11/17
*/

int execute_shellcmd(SHELLCMD *t)
{
    return exec_shellcmd(t, stdin, stdout);
}
