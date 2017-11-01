/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"

int exec_subshell(SHELLCMD *t, FILE *in, FILE *out)
{
    int pid = fork();
    if (pid == 0) {
        // We are the child process
        int status = exec_shellcmd(t->left, in, out);
        _exit(status);
    }
    if (pid > 0) {
        // We are the parent process
        int status = EXIT_SUCCESS;
        wait(&status);
        return WEXITSTATUS(status);
    } else {
        fprintf(stderr, "Could not fork process to execute subshell.\n");
        return EXIT_FAILURE;
    }
}
