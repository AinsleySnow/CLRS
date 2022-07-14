CC = gcc
CFLAGS = -Og -g -Wall -m64

all: Ex22-1-3 Ex22-1-4 Ex22-1-5 Ex22-1-6 Ex22-2-4 Ex22-2-7 Ex22-2-8 Ex22-2-9 Ex22-3-7 Ex22-3-10 Ex22-3-12 Ex22-3-13 BFS DFS FindSCC TopologicalSort

Ex22-1-3: Ex22-1-3.c
	$(CC) $(CFLAGS) -o Ex22-1-3 Ex22-1-3.c

Ex22-1-4: Ex22-1-4.c
	$(CC) $(CFLAGS) -o Ex22-1-4 Ex22-1-4.c

Ex22-1-5: Ex22-1-5.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o Ex22-1-5 List\List.c Ex22-1-5.c

Ex22-1-6: Ex22-1-6.c
	$(CC) $(CFLAGS) -o Ex22-1-6 Ex22-1-6.c

Ex22-2-4: Ex22-2-4.c Queue\Queue.c
	$(CC) $(CFLAGS) -o Ex22-2-4 Ex22-2-4.c Queue\Queue.c

Ex22-2-7: Ex22-2-7.c Queue\Queue.c
	$(CC) $(CFLAGS) -o Ex22-2-7 Ex22-2-7.c Queue\Queue.c

Ex22-2-8: Ex22-2-8.c Queue\Queue.c Queue\Queue.h
	$(CC) $(CFLAGS) -o Ex22-2-8 Ex22-2-8.c Queue\Queue.c

Ex22-2-9: Ex22-2-9.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o Ex22-2-9 Ex22-2-9.c List\List.c

Ex22-3-10: Ex22-3-10.c
	$(CC) $(CFLAGS) -o Ex22-3-10 Ex22-3-10.c

Ex22-3-12: Ex22-3-12.c
	$(CC) $(CFLAGS) -o Ex22-3-12 Ex22-3-12.c

Ex22-3-13: Ex22-3-13.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o Ex22-3-13 List\List.c Ex22-3-13.c

Ex22-4-2: Ex22-4-2.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o Ex22-4-2 List\List.c Ex22-4-2.c

Ex22-4-3: Ex22-4-3.c
	$(CC) $(CFLAGS) -o Ex22-4-3 Ex22-4-3.c

Ex22-4-5: Ex22-4-5.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o Ex22-4-5 Ex22-4-5.c List\List.c List\List.h

Ex22-5-5: Ex22-5-5.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o Ex22-5-5 Ex22-5-5.c List\List.c List\List.h

Ex22-5-6: Ex22-5-6.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o Ex22-5-6 Ex22-5-6.c List\List.c List\List.h

BFS: Samples/BFS.c Queue\Queue.c Queue\Queue.h
	$(CC) $(CFLAGS) -o BFS Queue\Queue.c Samples\BFS.c

DFS: Samples\DFS.c 
	$(CC) $(CFLAGS) -o DFS Samples\DFS.c

FindSCC: Samples\FindSCC.c
	$(CC) $(CFLAGS) -o FindSCC Samples\FindSCC.c

TopologicalSort: Samples\TopologicalSort.c List\List.c List\List.h
	$(CC) $(CFLAGS) -o TopologicalSort Samples\TopologicalSort.c List\List.c List\List.h