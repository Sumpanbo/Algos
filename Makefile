CC=gcc
CFLAGS=-std=c99 -g

heapsort: heapsort.c
	$(CC) -$(CFLAGS) -o $@ $<
