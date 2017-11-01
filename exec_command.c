/*
   CITS2002 Project 2 2017
   Name(s):     Alexander Rafferty, Dhaval Vaghjiani
   Student number(s):   21712241, 22258431
   Date:        03/11/17
*/

#include "myshell.h"
#include <sys/time.h>

int exec_cd(char *path)
{
    if (chdir(path) == 0) return 0;
    if (strchr(path, '/') != NULL) return EXIT_FAILURE;
    char *cdpath = CDPATH;
    while (true) {
        char *full_path = search_paths(&cdpath, path);
        if (full_path == NULL) break;
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
    int status = exec_command(t, in, out);
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
        return exec_time(t, in, out);
    }
    return exec_external_command(t->argv[0], t->argv, in, out);
}
