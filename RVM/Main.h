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
	map<string,Value*> VariableMap; 
public:
	Program();
	map<string,Value::VTYPE> typeMap; 
	Value* get(int index);
	Value* getFromTop();
	void pop();
	void remove(int index);
	int addValue(Value* value);
	size_t size();
	void addVariable(string name,string TYPE);
	void setVariable(string name,Value* pointer);
	Value* getVariable(string name);
	bool hasVariable(string name);
	void removeVariable(string name);
	void exit();
};

extern Program* program;

#endif
