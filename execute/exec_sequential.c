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
