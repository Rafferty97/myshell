/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"

int exec_shellcmd(SHELLCMD *t, FILE *in, FILE *out, bool ntl)
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
    switch (t->type) {
        case CMD_COMMAND:
        return exec_command(t, in, out, ntl);

        case CMD_SEMICOLON:
        case CMD_AND:
        case CMD_OR:
        return exec_sequential(t, in, out, ntl);

        case CMD_SUBSHELL:
        return exec_subshell(t, in, out, ntl);

        case CMD_PIPE:
        return exec_pipe(t, in, out, ntl);

        /*case CMD_BACKGROUND:
        return exec_background(t, in, out, ntl);
        */

        default:
        fprintf(stderr, "Unknown command type encountered.\n");
        return EXIT_FAILURE;
    }
    if (t->infile != NULL) fclose(in);
    if (t->outfile != NULL) fclose(out);
}
