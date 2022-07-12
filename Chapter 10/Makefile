CC = gcc
CFLAGS = -Og -g -Wall -m64
Q = Queue
S = stack

queue: $Q\Queue.c $Q\Queue.h $Q\test.c
	$(CC) $(CFLAGS) $Q\test.c $Q\Queue.c -o $Q\queue

stack: $S\stack.c $S\stack.h $S\test.c
	$(CC) $(CFLAGS) $S\test.c $S\stack.c -o $S\stack

Ex10-2-8: Ex10-2-8.c
	$(CC) $(CFLAGS) Ex10-2-8.c -o Ex10-2-8

Ex10-4-5: Ex10-4-5.c $S\stack.h $S\stack.c
	$(CC) $(CFLAGS) Ex10-4-5.c $S\stack.c "..\Chapter 12\bst\BinarySearchTree.c" -o Ex10-4-5

Ex10-4-6: Ex10-4-6.c
	$(CC) $(CFLAGS) Ex10-4-6.c -o Ex10-4-6