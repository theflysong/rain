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
	Value get(int index);
	Value getFromTop();
	void pop();
	int addValue(Value value);
};

extern Program* program;

#endif
