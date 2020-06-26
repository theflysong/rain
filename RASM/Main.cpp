#include "Main.h"
#include "ITranslator.h"

Program::Program(){	
}

Program::~Program(){
}

void Program::addVariable(string name)
{
	this->VariableMap[name]=true;
}

void Program::removeVariable(string name)
{
	if(hasVariable(name))
	{
		VariableMap.erase(name);
	}
}

bool Program::hasVariable(string name)
{
	return VariableMap.find(name)!=VariableMap.end(); 
} 

Program* program;

/*
	³ÌÐò¿ªÊ¼ 
*/
int main()
{
	program = new Program;
	string where;
	cin>>where;
	FileCStream* file = new FileCStream(where);
	delete program;
	delete file;
	return 0;
}
