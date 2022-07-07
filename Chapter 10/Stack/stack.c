#include "stack.h"
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

bool create_stack(stack* s, int size)
{
	s->stack = calloc(size, sizeof(long));
	if(!s->stack)
		return false;

	s->size = size;
	s->top = 0;
	return true;
}

void clear_stack(stack* s)
{
	free(s->stack);
	s->stack = NULL;
	s->top = 0;
	s->size = 0;
}

bool is_stack_empty(stack* s)
{
	return s->top == 0;
}

void push(stack* s, long x)
{
    s->stack[s->top] = x;
    if (s->top + 1 < s->size)
        s->top++;
}

long pop(stack* s)
{
	if(is_stack_empty(s))
		return LONG_MIN;
	s->top -= 1;
	return *(s->stack + s->top + 1);
}