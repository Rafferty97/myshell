/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"

int exec_sequential(SHELLCMD *t, FILE *in, FILE *out, bool ntl)
{
    int status;
    // Execute the left command
    status = exec_shellcmd(t->left, in, out, true);
    // Check for preceeding command's failure if && was used, or success if || was used
    if (t->type == CMD_AND && status != 0) return status;
    if (t->type == CMD_OR && status == 0) return status;
    // Execute the right command
    status = exec_shellcmd(t->right, in, out, ntl);
    return status;
}
