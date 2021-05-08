#inlcude "stack.h"

bool CreateAStack(Stack* s, int size)
{
	s->stack = malloc(size * sizeof(int));
	if(!s->stack)
		return false;
	return true;
}

bool Clear(Stack* s)
{
	free(s->stack);
	s->stack = NULL;
	s->top = 0;
}

bool IsStackEmpty(Stack* s)
{
	return s->top == 0;
}

void Push(Stack* s, int x)
{
	s->top += 1;
	*(s->stack + s->top) = x;
}

int Pop(Stack* s)
{
	if(IsStackEmpty(s))
		return INT_MIN;
	s->top -= 1;
	return *(s->stack + s->top + 1);
}



























