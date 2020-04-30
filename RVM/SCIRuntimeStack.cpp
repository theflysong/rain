#include "SCIRuntimeStack.h"

/*
	��õ�i��Ԫ�� 
*/
Value* RuntimeStack::get(int index)
{
	return stack[index];
}

Value* RuntimeStack::getFromTop()
{
	return stack[stack.size()-1];
}

void RuntimeStack::remove(int index)
{
	this->stack[index]=NULL;
	if(index==stack.size()-1){
		stack.pop_back();
	}
}

size_t RuntimeStack::size()
{
	return stack.size(); 
}

/*
	ѹ��һ��Ԫ�� 
*/
int RuntimeStack::push(Value* value)
{
	vector<Value*>::iterator it=find(stack.begin(),stack.end(),(Value*)NULL);
	if(it!=stack.end()){
		stack.insert(it,value);
		return distance(stack.begin(),it);
	}
	stack.push_back(value);
	return stack.size()-1;
}

/*
	����һ��Ԫ�� 
*/
void RuntimeStack::pop()
{
	stack.pop_back();
}
