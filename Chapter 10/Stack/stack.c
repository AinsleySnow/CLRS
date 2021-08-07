#include "stack.h"
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

bool create_stack(stack* s, int size)
{
	s->stack = malloc(size * sizeof(long));
	if(!s->stack)
		return false;
	for(int i = 0; i < size; ++i)
		s->stack[i] = 0;

	s->size = size;
	s->top = 0;
	return true;
}

bool clear_stack(stack* s)
{
	free(s->stack);
	s->stack = NULL;
	s->top = 0;
	s->size = 0;
}

bool is_stack_empty(stack s)
{
	return s.top == 0;
}

void push(stack* s, long x)
{
	s->top += 1;
	*(s->stack + s->top) = x;
}

long pop(stack* s)
{
	if(IsStackEmpty(s))
		return LONG_MIN;
	s->top -= 1;
	return *(s->stack + s->top + 1);
}