PROJECT = myshell
HEADERS = $(PROJECT).h
OBJ = execute.o globals.o myshell.o parser.o exec_command.o

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

exec_command.o : execute/exec_command.c
	$(C99) $(CFLAGS) -c execute/exec_command.c

clean:
	rm -f $(PROJECT) $(OBJ)
