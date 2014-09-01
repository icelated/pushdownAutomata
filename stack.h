//dynamically expanding stack
#ifndef STACK_H
#define STACK_H
const int INIT_STACK = 200;
class stack {
private:
	char* data;
	int top;
	void expandStack();
public:
	stack();
	~stack();
	bool push(char x);
	char pop();
	bool isEmpty();
	void clear();
};

#endif
