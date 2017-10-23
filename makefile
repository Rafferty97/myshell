PROJECT = myshell
HEADERS = $(PROJECT).h
OBJ = execute.o globals.o myshell.o parser.o

C99	= cc -std=c99
CFLAGS = -Wall -pedantic -Werror

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

clean:
	rm -f $(PROJECT) $(OBJ)
