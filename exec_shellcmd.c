/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"

int exec_shellcmd(SHELLCMD *t, FILE *in, FILE *out)
{
    if (t->infile != NULL) {
        in = fopen(t->infile, "r");
        if (in == NULL) {
            fprintf(stderr, "Could not open %s for reading.\n", t->infile);
            return EXIT_FAILURE;
        }
    }
    if (t->outfile != NULL) {
        out = fopen(t->outfile, t->append ? "a" : "w");
        if (out == NULL) {
            fprintf(stderr, "Could not open %s for writing.\n", t->infile);
            return EXIT_FAILURE;
        }
    }
    // Switch statement to determine the type of command and proceed accordingly
    int status;
    switch (t->type) {
        case CMD_COMMAND:
        status = exec_command(t, in, out);
        break;

        case CMD_SEMICOLON:
        case CMD_AND:
        case CMD_OR:
        status = exec_sequential(t, in, out);
        break;

        case CMD_SUBSHELL:
        status = exec_subshell(t, in, out);
        break;

        case CMD_PIPE:
        status = exec_pipe(t, in, out);
        break;

        /*case CMD_BACKGROUND:
        status = exec_background(t, in, out);
        break;
        */

        default:
        fprintf(stderr, "Unknown command type encountered.\n");
        status = EXIT_FAILURE;
    }
    if (t->infile != NULL) fclose(in);
    if (t->outfile != NULL) fclose(out);
    return status;
}
