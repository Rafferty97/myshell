/*
   CITS2002 Project 2 2017
   Name(s):     Alexander Rafferty, Dhaval Vaghjiani
   Student number(s):   21712241, 22258431
   Date:        03/11/17
*/

#include "../myshell.h"

int exec_sequential(SHELLCMD *t, FILE *in, FILE *out)
{
    int status;
    status = exec_shellcmd(t->left, in, out);
    if (t->type != CMD_SEMICOLON) {
        if (
            (t->type == CMD_AND && status != 0) || //If type is CMD_AND and the left command was unsuccessful
            (t->type == CMD_OR && status == 0) //If the type is CMD_OR and the left command was successful
        ) return status;
    }
    status = exec_shellcmd(t->right, in, out);
    return status;
}
