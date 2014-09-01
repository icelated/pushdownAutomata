#include "stack.h"
stack::stack()
{
	top = 0;
	data = new char[INIT_STACK];
}
stack::~stack()
{
	delete[ ] data;
}
void stack::expandStack()
{
	char* newdata = new char[top+INIT_STACK];
	for(int i=0;i<top;i++)
		newdata[i] = data[i];
	delete[ ] data;
	data = newdata;
}
bool stack::push(char x)
{
    if (top % INIT_STACK == 0)
        expandStack();
    data[top++] = x;
    return true;
}
char stack::pop()
{
    if (top == 0)
        return 'z';
    return data[--top];
}
bool stack::isEmpty()
{
	if (top == 0)
		return true;
	return false;
}
void stack::clear()
{
	top = 0;
}
