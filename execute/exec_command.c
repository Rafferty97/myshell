#include "../myshell.h"

int exec_external_command(char *filename, char **args)
{
    int pid = fork();
    if (pid == 0) {
        // We are the child process
        if (strchr(filename, '/') != NULL) {
            // Absolute path supplied
            execv(filename, args);
            // execv failed
            fprintf(stderr, "myshell: %s: No such file or directory", filename);
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
                strcpy(npath, filename);
                execv(full_path, args);
                // execv failed, try the next path
                path = strchr(path, ':');
                if (path == NULL) {
                    // No more paths to try
                    fprintf(stderr, "myshell: %s: command not found", filename);
                    exit(EXIT_FAILURE);
                }
                path++;
            }
        }
    }
    if (pid > 0) {
        // We are the parent process
        int status = EXIT_SUCCESS;
        wait(&status);
        return status;
    } else {
        fprintf(stderr, "Could not fork process to execute command.\n");
        return EXIT_FAILURE;
    }
}

int exec_command(SHELLCMD *t)
{
    // Check for an internal command
    // todo
    return exec_external_command(t->argv[0], t->argv);
}
