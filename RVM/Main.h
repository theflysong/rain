#ifndef __MAIN__
#define __MAIN__

/*
	��ͷ�ļ� 
*/ 
#include "head.h"
#include "SCI.h"
#include "FileCStream.h"

/*
	����
*/
class Program
{
private:
	RuntimeStack ValueStack;
	//map<string,int> map; 
public:
	Program();
	Value* get(int index);
	Value* getFromTop();
	void pop();
	void remove(int index);
	int addValue(Value* value);
	size_t size();
};

extern Program* program;

#endif
