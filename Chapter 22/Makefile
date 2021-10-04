CC = gcc
CFLAGS = -Og -Wall -m64
LIBS = -lm

all: Ex22-1-3 Ex22-1-4 Ex22-1-5 Ex22-1-6 Ex22-2-4 Ex22-2-7 Ex22-2-8 Ex22-2-9 Ex22-3-7 Ex22-3-10 Ex22-3-12 Ex22-3-13 BFS DFS FindSCC TopologicalSort

Ex22-1-3: Ex22-1-3.c
	$(CC) $(CFLAGS) $(LIBS) -o Ex22-1-3 Ex22-1-3.c

Ex22-1-4: Ex22-1-4.c
	$(CC) $(CFLAGS) $(LIBS) -o Ex22-1-4 Ex22-1-4.c

Ex22-1-5: Ex22-1-5.c List\List.c List\List.h
	$(CC) $(CFLAGS) $(LIBS) -o Ex22-1-5 List\List.c Ex22-1-5.c

Ex22-1-6: Ex22-1-6.c
	$(CC) $(CFLAGS) $(LIBS) -o Ex22-1-6 Ex22-1-6.c

Ex22-2-4: Ex22-2-4.c \Queue\Queue.c \Queue\Queue.h
	$(CC) $(CFLAGS) $(LIBS) -o Ex22-2-4 Ex22-2-4.c \Queue\Queue.c

Ex22-2-8: Ex22-2-8.c \Queue\Queue.c \Queue\Queue.h
	$(CC) $(CFLAGS) $(LIBS) -o Ex22-2-8 Ex22-2-8.c \Queue\Queue.c

Ex22-2-9: Ex22-2-9.c \List\List.c \List\List.h
	$(CC) $(CFLAGS) $(LIBS) -o Ex22-2-9 Ex22-2-9.c \List\List.c

BFS: Samples/BFS.c Queue\Queue.c Queue\Queue.h
	$(CC) $(CFLAGS) $(LIBS) -o BFS Queue\Queue.c Samples\BFS.c

DFS: Samples\DFS.c 
	$(CC) $(CFLAGS) $(LIBS) -o DFS Samples\DFS.c

FindSCC: Samples\FindSCC.c
	$(CC) $(CFLAGS) $(LIBS) -o FindSCC Samples\FindSCC.c

TopologicalSort: Samples\TopologicalSort.c
	$(CC) $(CFLAGS) $(LIBS) -o TopologicalSort Samples\TopologicalSort.c