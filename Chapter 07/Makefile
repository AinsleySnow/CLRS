CC = g++
CFLAGS = -Wall -Og -g
F = ../framework

Test: $F/test-sorting.cpp
	g++ $(CFLAGS) $F/test-sorting.cpp -c -o $F/test-sorting.o

QuickSort: Test QuickSort.c
	$(CC) $(CFLAGS) $F/test-sorting.o QuickSort.c -o QuickSort