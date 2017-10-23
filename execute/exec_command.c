#include "../myshell.h"

char *search_paths(char **path, char *suffix)
{
    static char full_path[4096];
    // If path points to NULL, no more paths to try
    if (*path == NULL) return NULL;
    char *fp = full_path;
    // Copy path variable into buffer
    strcpy(fp, *path);
    // Advance to the end of the current path prefix
    fp = strchr(full_path, ':');
    if (fp == NULL) {
        fp = full_path + strlen(full_path);
    }
    // Append a forward slash
    *fp++ = '/';
    // Append the filename
    strcpy(fp, suffix);
    // Advance the path pointer to the next prefix
    *path = strchr(*path, ':');
    if (*path != NULL) (*path)++;
    return full_path;
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
            execv(filename, args);
            // execv failed
            fprintf(stderr, "myshell: %s: No such file or directory", filename);
            _exit(EXIT_FAILURE);
        } else {
            // Relative path supplied, use PATH
            char *path = PATH;
            while (true) {
                char *full_path = search_paths(&path, filename);
                if (full_path == NULL) {
                    // No more paths to try
                    fprintf(stderr, "myshell: %s: command not found", filename);
                    _exit(EXIT_FAILURE);
                }
                execv(full_path, args);
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

int exec_cd(char *path)
{
    if (chdir(path) == 0) return 0;
    char *cdpath = CDPATH;
    while (true) {
        char *full_path = search_paths(&cdpath, path);
        if (full_path == NULL) break;
        if (chdir(full_path) == 0) return 0;
    }
    fprintf(stderr, "Could not change directory.\n");
    return EXIT_FAILURE;
}

int exec_command(SHELLCMD *t, FILE *in, FILE *out)
{
    if (strcmp(t->argv[0], "cd") == 0) {
        if (t->argc > 1) {
            return exec_cd(t->argv[1]);
        } else {
            return exec_cd(HOME);
        }
    }
    if (strcmp(t->argv[0], "time") == 0) {
        fprintf(stderr, "the time command is not yet implemented.\n");
        return EXIT_FAILURE;
    }
    return exec_external_command(t->argv[0], t->argv, in, out);
}
