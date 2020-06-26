#ifndef __MAIN__
#define __MAIN__

/*
	打开头文件 
*/ 
#include "head.h"
#include "FileCStream.h"

/*
	程序
*/
class Program
{
private:
	map<string,bool> VariableMap; 
public:
	Program();
	~Program();
	void addVariable(string name);
	bool hasVariable(string name);
	void removeVariable(string name);
};

extern Program* program;

#endif
