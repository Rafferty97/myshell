#include "../myshell.h"

int exec_sequential(SHELLCMD *t, FILE *in, FILE *out)
{
    int status;
    status = exec_shellcmd(t->left, in, out);
    if (t->type != CMD_SEMICOLON) {
        if (
            (t->type == CMD_AND && status != 0) ||
            (t->type == CMD_OR && status == 0)
        ) return status;
    }
    status = exec_shellcmd(t->right, in, out);
    return status;
}

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
