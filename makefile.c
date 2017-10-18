C99	=	cc -std=c99
CFLAGS =	-Wall -pedantic -Werror


myshell : execute.o globals.o myshell.o parser.o
	$(C99) $(CFLAGS) -o myshell \
			execute.o globals.o myshell.o parser.o -lm


myshell.o : myshell.c myshell.h
	$(C99) $(CFLAGS) -c myshell.c


globals.o : globals.c
	$(C99) $(CFLAGS) -c globals.c


parser.o : parser.c
	$(C99) $(CFLAGS) -c parser.c


execute.o : execute.c
	$(C99) $(CFLAGS) -c execute.c
