#include "SCIRuntimeStack.h"

/*
	获得从位于栈顶+1-index的元素 
*/
Value RuntimeStack::get(int index)
{
	return stack[stack.size()-index];
}

/*
	压入一个元素 
*/
void RuntimeStack::push(Value value)
{
	stack.push_back(value);
}

/*
	弹出一个元素 
*/
void RuntimeStack::pop()
{
	stack.pop_back();
}
