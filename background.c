/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"
#include <signal.h>

typedef struct {
    pid_t pid;
    bool done;
    int status;
} process;

size_t num_bk_proc = 0;
process bk_proc[256];

void sigchld_handler(int sig, siginfo_t *siginfo, void *vp)
{
    int status;
    for (int i=0; i<num_bk_proc; i++) {
        process *p = &bk_proc[i];
        if (p->pid == 0) continue;
        if (p->done) continue;
        if (waitpid(p->pid, &status, WNOHANG) > 0) {
            p->done = true;
            p->status = status;
        }
    }
}

void add_handler()
{
    struct sigaction sa;
    sa.sa_sigaction = &sigchld_handler;
    sa.sa_flags = SA_NOCLDSTOP | SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);
}

int exec_background(SHELLCMD *t, FILE *in, FILE *out)
{
    add_handler();
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Could not fork background process.\n");
        return EXIT_FAILURE;
    }
    if (pid == 0) {
        int status = exec_shellcmd(t->left, in, out);
        _exit(status);
    }
    bk_proc[num_bk_proc].pid = pid;
    bk_proc[num_bk_proc].done = false;
    num_bk_proc++;
    fprintf(stderr, "[%i]: Started\n", pid);
    return exec_shellcmd(t->right, in, out);
}

void check_bk_procs()
{
    for (int i=0; i<num_bk_proc; i++) {
        process *p = &bk_proc[i];
        if (p->pid == 0) continue;
        if (p->done) {
            fprintf(stderr, "[%i]: Finished with status %i\n", p->pid, p->status);
            p->pid = 0;
        }
    }
    while (num_bk_proc > 0 && bk_proc[num_bk_proc - 1].pid == 0) num_bk_proc--;
}
