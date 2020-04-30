#ifndef __MAIN__
#define __MAIN__

/*
	打开头文件 
*/ 
#include "head.h"
#include "SCI.h"
#include "FileCStream.h"

/*
	程序
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
