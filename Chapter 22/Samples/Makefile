CC = gcc
CFLAGS = -Og -Wall -m64
LIBS = -lm

all: BFS DFS FindSCC TopologicalSort

BFS: BFS.c ../Queue/Queue.c ../Queue/Queue.h
	$(CC) $(CFLAGS) $(LIBS) -o BFS ../Queue/Queue.c BFS.c

DFS: DFS.c 
	$(CC) $(CFLAGS) $(LIBS) -o DFS DFS.c

FindSCC: FindSCC.c ..\List\List.c ..\List\List.h
	$(CC) $(CFLAGS) $(LIBS) -o FindSCC FindSCC.c ..\List\List.c

TopologicalSort: TopologicalSort.c ..\List\List.c ..\List\List.h
	$(CC) $(CFLAGS) $(LIBS) -o TopologicalSort TopologicalSort.c ..\List\List.c
