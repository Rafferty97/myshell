PROJECT = myshell
HEADERS = $(PROJECT).h
OBJ = execute.o globals.o myshell.o parser.o exec_command.o exec_shellcmd.o exec_sequential.o exec_subshell.o exec_pipe.o

C99	= gcc -std=c99
CFLAGS = -Wall -pedantic -Werror -g

# TODO: employ automatic variables (refer to lecture 13, slide 15)
$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm


myshell.o : myshell.c $(HEADERS)
	$(C99) $(CFLAGS) -c myshell.c

globals.o : globals.c
	$(C99) $(CFLAGS) -c globals.c

parser.o : parser.c
	$(C99) $(CFLAGS) -c parser.c

execute.o : execute.c
	$(C99) $(CFLAGS) -c execute.c

exec_shellcmd.o : execute/exec_shellcmd.c
	$(C99) $(CFLAGS) -c execute/exec_shellcmd.c

exec_command.o : execute/exec_command.c
	$(C99) $(CFLAGS) -c execute/exec_command.c

exec_sequential.o : execute/exec_sequential.c
	$(C99) $(CFLAGS) -c execute/exec_sequential.c

exec_subshell.o : execute/exec_subshell.c
	$(C99) $(CFLAGS) -c execute/exec_subshell.c

exec_pipe.o : execute/exec_pipe.c
	$(C99) $(CFLAGS) -c execute/exec_pipe.c

clean:
	rm -f $(PROJECT) $(OBJ)
