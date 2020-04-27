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
		vector<Value> stack;
	public:
		Value get(int index=1);
		void push(Value value);
		void pop();
}; 

#endif
