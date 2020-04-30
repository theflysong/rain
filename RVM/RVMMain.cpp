#include "Main.h"
#include "Execute.h"

int Program::addValue(Value* value)
{
	ValueStack.push(value);
	return ValueStack.size()-1;
}

Value* Program::get(int index)
{
	return ValueStack.get(index);
}

Value* Program::getFromTop()
{
	return ValueStack.getFromTop();
}

void Program::pop()
{
	delete ValueStack.getFromTop();
	ValueStack.pop();
}

Program::Program()
{
	
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
	Executer exe(file);
	int re = exe.execute();
	delete program;
	delete file;
	return re;
}
