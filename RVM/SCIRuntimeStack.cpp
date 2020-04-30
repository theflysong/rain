#include "SCIRuntimeStack.h"

/*
	获得第i个元素 
*/
Value* RuntimeStack::get(int index)
{
	return stack[index];
}

Value* RuntimeStack::getFromTop(){
	return stack[stack.size()-1];
}

size_t RuntimeStack::size()
{
	return stack.size(); 
}

/*
	压入一个元素 
*/
void RuntimeStack::push(Value* value)
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
