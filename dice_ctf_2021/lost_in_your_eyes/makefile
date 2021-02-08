CC=gcc
CFLAGS=-Wall

all:
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm -f main
	rm -rf mem
	mkdir mem

test: clean all
	./main