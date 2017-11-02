/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"

int exec_pipe(SHELLCMD *t, FILE *in, FILE *out, bool ntl)
{
    int fd[2];
    pipe(fd);
    if (DEBUG_FORKS) fprintf(stderr, "Forking\n");
    pid_t pid_left = fork();
    if (pid_left < 0) {
        fprintf(stderr, "Could not fork process to execute pipeline.\n");
        return EXIT_FAILURE;
    }
    if (pid_left == 0) {
        close(fd[0]);
        FILE *pipe_out = fdopen(fd[1], "w");
        int status = exec_shellcmd(t->left, in, pipe_out, false);
        close(fd[1]);
        _exit(status);
    }
    close(fd[1]);
    FILE *pipe_in = fdopen(fd[0], "r");
    int status = exec_shellcmd(t->right, pipe_in, out, true);
    waitpid(pid_left, NULL, 0);
    close(fd[0]);
    fprintf(stderr, "PIPE DONE\n");
    return status;
}
