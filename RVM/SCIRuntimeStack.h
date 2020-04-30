#ifndef __SCI_STACK_BASICSTACK__
#define __SCI_STACK_BASICSTACK__

#include "head.h"
#include "Value.h"

/*
	≥Ã–Ú’ª 
*/ 
class RuntimeStack
{
private:
	vector<Value*> stack;
public:
	Value* get(int index=0);
	Value* getFromTop();
	size_t size();
	void push(Value *value);
	void pop();
}; 

#endif
