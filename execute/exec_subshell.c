#include "../myshell.h"

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
