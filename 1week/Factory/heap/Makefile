CC = gcc

CFLAGS = -O2 -std=c99 -pedantic -Wall -o -lm

ex2.11: doubleHeapSize.c heap.c main.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean debug-ex2.11

clean:
	rm -f ex2.11

debug-ex2.11: ex2.11
	cat ../@tests/1.in | valgrind ./ex2.11
