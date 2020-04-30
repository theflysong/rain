#include "SCIRuntimeStack.h"

/*
	获得第i个元素 
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
	压入一个元素 
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
	弹出一个元素 
*/
void RuntimeStack::pop()
{
	stack.pop_back();
}
