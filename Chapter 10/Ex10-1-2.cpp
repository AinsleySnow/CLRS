//10.1-2
#include <iostream>
#include <memory>
#include <exception>

using namespace std;

bool IsStackOverflow();
bool Stack1Push(int x);
bool Stack2Push(int x);
int Stack1Pop();
int Stack2Pop();
bool IsStack1Empty();
bool IsStack2Empty();
void PrintStack1();
void PrintStack2();

unique_ptr<int> array;
int s1top = -1, s2top = 0;
//making original value of s1top equals -1 and making that of s2top equals 'size'
//ensures the functions below can get correct size of two stacks when there is no element
//in either stack

#pragma region codes used for test
int main(void)
{
	int size = 10;
	//cin >> size;
	s2top = size;
	array = make_unique<int>(size);
	
	try
	{
		Stack1Pop();
	}
	catch
	{
		cout << "An exception has been throwed."
	}
	try
	{
		Stack2Pop();
	}
	catch
	{
		cout << "An exception has been throwed."
	}
	
	Stack1Push(200);
	Stack1Push(30);
	PrintStack1();
	Stack2Push(4);
	Stack2Push(7);
	PrintStack2();
	
	while(Stack1Push(5));
	PrintStack1();
	PrintStack2();
	
	array = make_unique<int>(size);
	
	while(Stack2Push(9));
	PrintStack1();
	PrintStack2();
	
	return 0;
}

void PrintStack1()
{
	if(IsStack1Empty())
	{
		cout << "Stack1 is empty." << endl;
		return;
	}
	cout << "Things in stack1:" << endl;
	for(int i = 0; i <= s1top; ++i)
		cout << *(array + i) << ' ';
	cout << endl;
}

void PrintStack2()
{
	if(IsStack2Empty())
	{
		cout << "Stack2 is empty." << endl;
		return;
	}
	cout << "Things in stack2:" << endl;
	for(int i = size - 1; i >= s2top; --i)
		cout << *(array + i) << ' ';
	cout << endl;
}

#pragma endregion

bool IsStackOverflow()
{
	return s1top + 1 + size - s2top == size;
}

bool Stack1Push(int x)
{
	++s1top;
	if(IsStackOverflow())
	{
		--s1top;
		return false;
	}
	*(array + s1top) = x;
	return true;
}

bool Stack2Push(int x)
{
	--s2top;
	if(IsStackOverflow())
	{
		++s2top;
		return false;
	}
	*(array + s2top) = x;
	return true;
}

int Stack1Pop()
{
	if(IsStack1Empty())
		throw out_of_range();
	
	--s1top;
	return *(array + s1top + 1);
}

int Stack2Pop()
{
	if(IsStack2Empty())
		throw out_of_range();
	
	++s2top;
	return *(array + s2top - 1);
}

bool IsStack1Empty()
{
	return s1top == -1;
}

bool IsStack2Empty()
{
	return s2top == size;
}