CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lm

main: main.o bcdopps.o
	$(CC) $(CFLAGS) -o main main.o bcdopps.o $(LIBS)

main.o: main.c bcdopps.h
	$(CC) $(CFLAGS) -c main.c

bcdopps.o: bcdopps.c bcdopps.h
	$(CC) $(CFLAGS) -c bcdopps.c

clean:
	rm -f *.o main
