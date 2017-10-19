int status;
int pid = fork();

// fork() returns 0 to the child process
if(pid == 0)
{
	//extract the command from the input
	char command[] = argv[1];
	//extract the arguments (if any) from the input
	if(cmd.argc > 2){
		char arguments[cmd.argc - 1][];
		//TODO: extract the arguments using the getopt() function and store them in the arguments array

	}
	
	execv(command, arguments);
	exit(EXIT_SUCCESS);
}
// Parent process
else if(pid > 0)
{
    
	wait(&status);
	exit(EXIT_SUCCESS) //get rid of this line, as we don't want parent process to terminate unless exit() is invoked?
}
//Else an error occurred
else
{
	perror("The creation of a child process via fork() failed");
	exit(EXIT_FAILURE);
}	