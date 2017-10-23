#include "myshell.h"
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
   CITS2002 Project 2 2017
   Name(s):		Alexander Rafferty, Dhaval Vaghjiani
   Student number(s):	21712241, 22258431
   Date:		03/11/17
*/

// -------------------------------------------------------------------

//THIS FUNCTION SHOULD BE CALLED IF THE COMMAND TO BE EXECUTED = "exit"
/* void exit_shell(bool arg_provided, int exit_status){
    if(!arg_provided){
        exit(last_exit_status);
    }
    else{
        exit(exit_status);
    }   
}


//THIS FUNCTION SHOULD BE CALLED IF THE COMMAND TO BE EXECUTED = "cd"
void change_directory(bool arg_provided, char *directory){
    if(!arg_provided){
        chdir(HOME);
    }
    else{
        if(strchr(directory, '/') != NULL){
            chdir(directory);
        }
        else{
            //try to find the given directory using CDPATH. If found, call chdir, else throw an error
        }
    }
}

//THE FOLLOWING FUNCTION SHOULD BE CALLED IF THE COMMAND TO BE EXECUTED = "time"
void time_command() {
    int pid = fork();
    if (pid == 0) {
        // We are the child process
        //execute the next command, and store the time it takes to do so in the time variable
    }
    if (pid > 0) {
        // We are the parent process. Wait for child process to finish.
        wait(&last_exit_status);
    } 
    else {
        fprintf(stderr, "Could not fork process to execute command.\n");
        exit(EXIT_FAILURE);
    }
    long tv_usec = 2000;
    fprintf(stderr, "Time taken for command: %limsec\n", tv_usec / 1000);
}
 */

int execute_shellcmd(SHELLCMD *t)
{
    switch (t->type) {
        case CMD_COMMAND:
        return exec_command(t);

        /*case CMD_SEMICOLON:
        case CMD_AND:
        case CMD_OR:
        return exec_sequential(t);

        case CMD_SUBSHELL:
        return exec_subshell(t);

        case CMD_PIPE:
        return exec_pipe(t);

        case CMD_BACKGROUND:
        return exec_background(t);
        */

        default:
        fprintf(stderr, "Unknown command type encountered.\n");
        return EXIT_FAILURE;
    }
}
