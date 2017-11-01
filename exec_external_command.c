#include "myshell.h"
#include <errno.h>

void exec_executable(char *filename, char **args)
{
    // Attempt to execute file
    execv(filename, args);
    // execv failed, assume it is a shell script
    FILE *script;
    script = fopen(filename, "r");
    dup2(fileno(script), STDIN_FILENO);
    execv(argv0, args);
}

int exec_external_command(char *filename, char **args, FILE *in, FILE *out)
{
    // Fork the process
    int pid = fork();
    if (pid == 0) {
        // We are the child process
        dup2(fileno(in), STDIN_FILENO);
        dup2(fileno(out), STDOUT_FILENO);
        // Attempt to execute the external command
        if (strchr(filename, '/') != NULL) {
            // Absolute path supplied
            if (access(filename, X_OK) == 0) {
                exec_executable(filename, args);
            }
            switch (errno) {
                case ENOENT:
                fprintf(stderr, "%s: No such file or directory", filename);
                break;
                case ENOTDIR:
                fprintf(stderr, "%s: Not a directory", filename);
                break;
                case EACCES:
                fprintf(stderr, "%s: Permission denied", filename);
                break;
                default:
                fprintf(stderr, "%s: Could not open", filename);
            }
            _exit(EXIT_FAILURE);
        } else {
            // Relative path supplied, use PATH
            char *path = PATH;
            while (true) {
                char *full_path = search_paths(&path, filename);
                if (full_path == NULL) {
                    // No more paths to try
                    fprintf(stderr, "%s: command not found", filename);
                    _exit(EXIT_FAILURE);
                }
                if (access(full_path, X_OK) == 0) {
                    exec_executable(full_path, args);
                }
            }
        }
    }
    if (pid > 0) {
        // We are the parent process
        int status = EXIT_SUCCESS;
        wait(&status);
        return WEXITSTATUS(status);
    } else {
        fprintf(stderr, "Could not fork process to execute external command.\n");
        return EXIT_FAILURE;
    }
}
