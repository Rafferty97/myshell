/*
   CITS2002 Project 2 2017
   Name(s):     Alexander Rafferty, Dhaval Vaghjiani
   Student number(s):   21712241, 22258431
   Date:        03/11/17
*/

#include "myshell.h"

int exec_pipe(SHELLCMD *t, FILE *in, FILE *out)
{
    int fd[2];
    pipe(fd);
    pid_t pid_left = fork();
    if (pid_left < 0) {
        fprintf(stderr, "Could not fork process to execute pipeline.\n");
        return EXIT_FAILURE;
    }
    if (pid_left == 0) {
        close(fd[0]);
        FILE *pipe_out = fdopen(fd[1], "w");
        int status = exec_shellcmd(t->left, in, pipe_out);
        close(fd[1]);
        _exit(status);
    }
    pid_t pid_right = fork();
    if (pid_right < 0) {
        fprintf(stderr, "Could not fork process to execute pipeline.\n");
        return EXIT_FAILURE;
    }
    if (pid_right == 0) {
        close(fd[1]);
        FILE *pipe_in = fdopen(fd[0], "r");
        int status = exec_shellcmd(t->right, pipe_in, out);
        close(fd[0]);
        _exit(status);
    }
    close(fd[0]);
    close(fd[1]);
    int status_left = EXIT_SUCCESS;
    int status_right = EXIT_SUCCESS;
    waitpid(pid_left, &status_left, 0);
    waitpid(pid_right, &status_right, 0);
    status_left = WEXITSTATUS(status_left);
    if (status_left != 0) return status_left;
    status_right = WEXITSTATUS(status_right);
    if (status_right != 0) return status_right;
    return EXIT_SUCCESS;
}