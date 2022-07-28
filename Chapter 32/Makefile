CC = gcc
CFLAGS = -Og -g -Wall -m64

S = Samples
F = ../framework

automaton: $S/FA.c
	$(CC) $(CFLAGS) $S/FA.c $F/tables.c -o $S/FA

Ex32-1-2: Ex32-1-2.c
	$(CC) $(CFLAGS) Ex32-1-2.c -o Ex32-1-2