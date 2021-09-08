# Makefile Variables
CC       = gcc
EXEC     = program
CFLAGS = -Wall -ansi -pedantic
OBJ      = maze.o map.o terminal.o makeMaze.o printMap.o
# Add FANCY to the CFLAGS and recompile the program
ifdef DARK
CFLAGS += -D DARK
DARK : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

maze.o : maze.c map.h terminal.h
	$(CC) $(CFLAGS) maze.c -c 

map.o : map.c map.h
	$(CC) $(CFLAGS) map.c -c

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) terminal.c -c

makeMaze.o : makeMaze.c makeMaze.h
	$(CC) $(CFLAGS) makeMaze.c -c	

printMap.o : printMap.c printMap.h
	$(CC) $(CFLAGS) printMap.c -c

	
clean:
	rm -f $(EXEC) $(OBJ)
