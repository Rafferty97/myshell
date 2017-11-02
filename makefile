PROJECT = myshell
HEADERS = $(PROJECT).h
OBJ = globals.o myshell.o parser.o exec_command.o exec_external_command.o exec_shellcmd.o exec_sequential.o exec_subshell.o exec_pipe.o background.o

C99	= gcc -std=c99
CFLAGS = -Wall -pedantic -Werror
$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ)

%.o : %.c $(HEADERS)
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)
