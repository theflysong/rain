#include "SCIRuntimeStack.h"

/*
	��ô�λ��ջ��+1-index��Ԫ�� 
*/
Value RuntimeStack::get(int index)
{
	return stack[stack.size()-index];
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
