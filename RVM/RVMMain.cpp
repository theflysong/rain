#include "Main.h"
#include "Execute.h"

int Program::addValue(Value* value)
{
	return ValueStack.push(value);
}

Value* Program::get(int index)
{
	return ValueStack.get(index);
}

Value* Program::getFromTop()
{
	return ValueStack.getFromTop();
}

size_t Program::size(){
	return ValueStack.size();
} 

void Program::remove(int index){
	delete ValueStack.get(index);
	ValueStack.remove(index);
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
	//delete file;
	return re;
}
