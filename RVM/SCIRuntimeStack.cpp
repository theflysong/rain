#include "SCIRuntimeStack.h"

/*
	��õ�i��Ԫ�� 
*/
Value RuntimeStack::get(int index)
{
	cout<<stack[index];
	return stack[index];
}

Value RuntimeStack::getFromTop(){
	return stack[stack.size()-1];
}

int RuntimeStack::size()
{
	return (int)stack.size(); 
}

/*
	ѹ��һ��Ԫ�� 
*/
void RuntimeStack::push(Value value)
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
