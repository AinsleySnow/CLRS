#pragma once
#include <stdlib.h>
#include <limits.h>

bool IsStackEmpty(Stack s);
void Push(Stack* s, int x);
int Pop(Stack* stack);
bool CreateAStack(Stack* s, int size);
bool Clear(Stack* s);

typedef struct Stack
{
	int* stack;
	int top;
}Stack;
