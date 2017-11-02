/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"
#include <sys/time.h>

int exec_cd(char *path)
{
    // Try as a relative path
    if (chdir(path) == 0) return 0;
    // If path commences with a /, do not search CDPATH
    if (path[0] == '/') return EXIT_FAILURE;
    // Search CDPATH
    char *cdpath = CDPATH;
    while (true) {
        char *full_path = search_paths(&cdpath, path);
        // If no more paths to try, exit loop
        if (full_path == NULL) break;
        // Try the full path
        if (chdir(full_path) == 0) return 0;
    }
    fprintf(stderr, "Could not change directory.\n");
    return EXIT_FAILURE;
}

int exec_time(SHELLCMD *t, FILE *in, FILE *out)
{
    struct timeval tv1, tv2;
    // Start timing
    gettimeofday(&tv1, NULL);
    // Execute the command
    t->argc--;
    t->argv++;
    int status = exec_command(t, in, out, true);
    t->argc++;
    t->argv--;
    // End timing
    gettimeofday(&tv2, NULL);
    // Print the elapsed time to sterr
    fprintf (stderr, "Execution time = %f msec\n",
        1000*((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
        (double) (tv2.tv_sec - tv1.tv_sec)));
    return status;
}

int exec_command(SHELLCMD *t, FILE *in, FILE *out, bool ntl)
{
    // Check for internal commands
    if (strcmp(t->argv[0], "cd") == 0) {
        if (t->argc > 1) {
            return exec_cd(t->argv[1]);
        } else {
            return exec_cd(HOME);
        }
    }
    if (strcmp(t->argv[0], "time") == 0) {
        return exec_time(t, in, out);
    }
    // Must be an external command
    return exec_external_command(t->argv[0], t->argv, in, out, ntl);
}
