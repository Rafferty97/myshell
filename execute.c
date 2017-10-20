#include "myshell.h"

/*
   CITS2002 Project 2 2017
   Name(s):		student-name1 (, student-name2)
   Student number(s):	student-number-1 (, student-number-2)
   Date:		date-of-submission
 */

// -------------------------------------------------------------------

//  THIS FUNCTION SHOULD TRAVERSE THE COMMAND-TREE and EXECUTE THE COMMANDS
//  THAT IT HOLDS, RETURNING THE APPROPRIATE EXIT-STATUS.
//  READ print_shellcmd0() IN globals.c TO SEE HOW TO TRAVERSE THE COMMAND-TREE

int execute_shellcmd(SHELLCMD *t)
{
    int status = EXIT_SUCCESS;

    if (t->type == CMD_COMMAND) {
        int pid = fork();
        if (pid == 0) {
            // We are the child process
            execv(t->argv[0], t->argv);
            // If execv is successful, this line won't be executed
            fprintf(stderr, "Problem executing execv.\n");
            exit(EXIT_FAILURE);
        }
        if (pid > 0) {
            // We are the parent process
            wait(&status);
        } else {
            fprintf(stderr, "Could not fork process to execute command.\n");
            exit(EXIT_FAILURE);
        }
    }

    return status;
}
