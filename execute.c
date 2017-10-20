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

bool execute_command(char *bin, char **args, int *status)
{
    int pid = fork();
    if (pid == 0) {
        // We are the child process
        if (strchr(bin, '/') != NULL) {
            // Absolute path supplied
            execv(bin, args);
            // execv failed
            fprintf(stderr, "myshell: %s: No such file or directory", bin);
            exit(EXIT_FAILURE);
        } else {
            // Relative path supplied, use PATH
            char *path = getenv("PATH");
            while (true) {
                char full_path[2048];
                strcpy(full_path, path);
                char *npath = strchr(full_path, ':');
                if (npath == NULL) {
                    npath = full_path + strlen(full_path);
                }
                *npath++ = '/';
                strcpy(npath, bin);
                execv(full_path, args);
                // execv failed, try the next path
                path = strchr(path, ':');
                if (path == NULL) {
                    // No more paths to try
                    fprintf(stderr, "myshell: %s: command not found", bin);
                    exit(EXIT_FAILURE);
                }
                path++;
            }
        }
    }
    if (pid > 0) {
        // We are the parent process
        wait(status);
    } else {
        fprintf(stderr, "Could not fork process to execute command.\n");
        exit(EXIT_FAILURE);
    }
    return true;
}

int execute_shellcmd(SHELLCMD *t)
{
    int status = EXIT_SUCCESS;

    if (t->type == CMD_COMMAND) {
        execute_command(t->argv[0], t->argv, &status);
    }

    return status;
}
