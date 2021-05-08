#pragma once
#include <random>

struct SinglyLinkedList
{
	int value;
	SinglyLinkedList* next;
};

void AutoGenerateAList(int size);