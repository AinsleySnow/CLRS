#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

typedef struct stack
{
	long* stack;
	int top;
	int size;
} stack;

bool is_stack_empty(stack* s);
void push(stack* s, long x);
long pop(stack* s);
bool create_stack(stack* s, int size);
void clear_stack(stack* s);

#endif /* _STACK_H_ */