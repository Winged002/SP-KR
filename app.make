CC = gcc
CFLAGS = -Wall -Wextra -std=c11

main: Main.o bcdopps.o
	$(CC) $(CFLAGS) -o main Main.o bcdopps.o

Main.o: Main.c bcdopps.h
    $(CC) $(CFLAGS) -c Main.c

bcdopps.o: bcdopps.c bcdopps.h
    $(CC) $(CFLAGS) -c bcdopps.c

clean:
rm -f *.o main
