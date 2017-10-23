#include "../myshell.h"

int exec_shellcmd(SHELLCMD *t, FILE *in, FILE *out)
{
    switch (t->type) {
        case CMD_COMMAND:
        return exec_command(t, in, out);

        case CMD_SEMICOLON:
        case CMD_AND:
        case CMD_OR:
        return exec_sequential(t, in, out);

        case CMD_SUBSHELL:
        return exec_subshell(t, in, out);

        /*case CMD_PIPE:
        return exec_pipe(t, in, out);

        case CMD_BACKGROUND:
        return exec_background(t, in, out);
        */

        default:
        fprintf(stderr, "Unknown command type encountered.\n");
        return EXIT_FAILURE;
    }
}
