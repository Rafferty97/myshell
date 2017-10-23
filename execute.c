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


//Global variable that indicates the exit-status of the most recently executed command
int recent_exit_status;

//  THIS FUNCTION SHOULD TRAVERSE THE COMMAND-TREE and EXECUTE THE COMMANDS
//  THAT IT HOLDS, RETURNING THE APPROPRIATE EXIT-STATUS.
//  READ print_shellcmd0() IN globals.c TO SEE HOW TO TRAVERSE THE COMMAND-TREE

bool execute_command(char *bin, char **args, int *status)
{
    int pid = fork();
    if (pid == 0) {
        // We are the child process
        if (strchr(bin, '/') != NULL) {
            // Absolute path supplied
            execv(bin, args);
            // execv failed
            fprintf(stderr, "myshell: %s: No such file or directory", bin);
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
                strcpy(npath, bin);
                execv(full_path, args);
                // execv failed, try the next path
                path = strchr(path, ':');
                if (path == NULL) {
                    // No more paths to try
                    fprintf(stderr, "myshell: %s: command not found", bin);
                    exit(EXIT_FAILURE);
                }
                path++;
            }
        }
    }
    if (pid > 0) {
        // We are the parent process
        wait(status);
    } else {
        fprintf(stderr, "Could not fork process to execute command.\n");
        exit(EXIT_FAILURE);
    }
    return true;
}




//THIS FUNCTION SHOULD BE CALLED IF THE COMMAND TO BE EXECUTED = "exit"
void exit_shell(bool arg_provided, int exit_status){
    if(!arg_provided){
        exit(recent_exit_status);
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
void time(){
    int pid = fork();
    if (pid == 0) {
        // We are the child process
        //execute the next command, and store the time it takes to do so in the time variable
    }
    if (pid > 0) {
        // We are the parent process. Wait for child process to finish.
        wait(status);
    } 
    else {
        fprintf(stderr, "Could not fork process to execute command.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "Time taken for command: %imsec\n", time);
}


int execute_shellcmd(SHELLCMD *t)
{
    int status = EXIT_SUCCESS;

    if (t->type == CMD_COMMAND) {
        execute_command(t->argv[0], t->argv, &status);
    }

    return status;
}
