CC=gcc
CFLAGS=-I.
DEPS = quicklib.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pokeristars: main.c
	gcc -Wall -std=c99 -O3 -o pokeristars.out main.c quicklib.c pokerlib.c quicklib.h pokerlib.h
