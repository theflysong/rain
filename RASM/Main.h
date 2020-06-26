#ifndef __MAIN__
#define __MAIN__

/*
	��ͷ�ļ� 
*/ 
#include "head.h"
#include "FileCStream.h"

/*
	����
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
