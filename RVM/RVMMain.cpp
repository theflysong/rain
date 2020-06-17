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

/*
	-1为NULL
*/
void Program::addVariable(string name,string type)
{
	this->VariableMap[name]=(Value*)NULL;
}

void Program::setVariable(string name,Value* pointer)
{
	if(hasVariable(name)){
		this->VariableMap[name]=pointer;
	}
}

void Program::removeVariable(string name)
{
	if(hasVariable(name))
	{
		delete getVariable(name);
		VariableMap.erase(name);
	}
}

void Program::exit(){
	while(this->size()==0){
		this->pop();
	}
	map<string,Value*>::iterator it = VariableMap.begin();
	while(it!=VariableMap.end()){
		delete it->second;
		it++;
	}
}

bool Program::hasVariable(string name)
{
	return VariableMap.find(name)!=VariableMap.end(); 
} 

Value* Program::getVariable(string name)
{
	if(hasVariable(name))
	{
		return VariableMap[name];
	}
	return (Value*)NULL;
}

Program* program;

/*
	程序开始 
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
