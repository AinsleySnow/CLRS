#include "LinkedList.h"

SinglyLinkedList head{ 0,nullptr };
SinglyLinkedList* current = nullptr;

void AutoGenerateAList(int size)
{
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(1, 6);
	
	for (int i = 0; i < size; ++i)
	{
		cout << dist(gen) << " "; // pass the generator to the distribution.
	}
}