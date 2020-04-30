#include "SCIRuntimeStack.h"

/*
	��õ�i��Ԫ�� 
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
	ѹ��һ��Ԫ�� 
*/
void RuntimeStack::push(Value* value)
{
	stack.push_back(value);
}

/*
	����һ��Ԫ�� 
*/
void RuntimeStack::pop()
{
	stack.pop_back();
}
