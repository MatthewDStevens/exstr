# TODO: Add dynamic linked library compile target or create new file
# TODO: Add test code target or create new file

OBJECTS = exstr.o
CC = gcc
CFLAGS = -std=c11 -c
CFLAGS_DEBUG = -std=c11 -ggdb3 -c
CFLAGS_TEST = -std=c11 -c

exstr.o: exstr.c exstr.h
	$(CC) $(CFLAGS) -c -o exstr.o exstr.c

clean:
	rm -f ./src/*.o