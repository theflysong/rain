#include "SCIRuntimeStack.h"

/*
	��õ�i��Ԫ�� 
*/
Value* RuntimeStack::get(int index)
{
	return stack[index];
}

/*
	���ջ��Ԫ�� 
*/
Value* RuntimeStack::getFromTop()
{
	return stack[stack.size()-1];
}

/*
	�Ƴ���index��Ԫ��(��ΪNULL���û����stack����) 
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
	ѹ��һ��Ԫ�� 
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
	����һ��Ԫ�� 
*/
void RuntimeStack::pop()
{
	stack.pop_back();
}
