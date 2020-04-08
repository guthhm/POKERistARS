CC=gcc
CFLAGS=-I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pokeristars: main.c
	gcc -w -o pokeristars.out main.c 
	./pokeristars.out
