PROJECT = myshell
HEADERS = $(PROJECT).h
OBJ = execute.o globals.o myshell.o parser.o exec_command.o exec_external_command.o exec_shellcmd.o exec_sequential.o exec_subshell.o exec_pipe.o

C99	= gcc -std=c99
CFLAGS = -Wall -pedantic -Werror -g
# Is the -g flag above meant to be there?
# TODO: employ automatic variables (refer to lecture 13, slide 15)
$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ) #-lm

%.o : %.c $(HEADERS)
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)
