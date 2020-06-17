#include "SCIRuntimeStack.h"

/*
	获得第i个元素 
*/
Value* RuntimeStack::get(int index)
{
	return stack[index];
}

/*
	获得栈顶元素 
*/
Value* RuntimeStack::getFromTop()
{
	return stack[stack.size()-1];
}

/*
	移除第index个元素(设为NULL待用或减少stack长度) 
*/
void RuntimeStack::remove(int index)
{
	this->stack[index]=NULL;
	while(stack[stack.size()-1]==NULL){
		stack.pop_back();
		if(stack.size()==0){
			break;
		}
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
		int ptr=distance(stack.begin(),it);
		stack.insert(it,value);
		return ptr;
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
