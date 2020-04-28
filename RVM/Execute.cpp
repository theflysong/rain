#include "Execute.h"
#include "CFunctions.h"

Executer::Executer(ICStream* stream)
{
	this->stream=stream;
	/*Instruction*/
	optCodeMap["push"]=SCIInstruction::PUSH;
	optCodeMap["nop"]=SCIInstruction::NOP;
	optCodeMap["exit"]=SCIInstruction::EXIT;
	optCodeMap["pop"]=SCIInstruction::POP;
	optCodeMap["jmp"]=SCIInstruction::JMP;
	optCodeMap["call"]=SCIInstruction::CALL;
	optCodeMap["mov"]=SCIInstruction::MOV;
	
	/*CFunction*/
	CFunctionMap["print"]=print; 
}

inline bool isNumber(string str)
{
	for(int i=0;i<str.length();i++){
		if(!isalnum(str[i]))
			return false;
	}
	return true;
}

inline int toNumber(string str)
{
	return atoi(str.c_str());
}

inline bool isDecimal(string str)
{
	for(int i=0;i<str.length();i++){
		if(!(isalnum(str[i])||str[i]=='.'))
			return false;
	}
	return true;
}

inline double toDecimal(string str)
{
	return atof(str.c_str());
}

inline bool isString(string str)
{
	return str[0]=='"'&&str[str.length()-1]=='"';
}

inline string toString(string str)
{
	string s="";
	for(int i=1;i<str.length()-1;i++)
	{
		s+=str[i];
	}
	escape(s);
	return s;
}

SCIInstruction Executer::getSource()
{
	string opt="";
	int arg1,arg2,arg3;
	string arg="";
	char ch=stream->read();
	while(!(isalnum(ch)||ch==ICStream::eos)){
		ch=stream->read();
	}
	while(isalnum(ch)){
		opt+=ch;
		ch=stream->read();
	}
	if(ch=='\n'||ch=='\r'||ch==ICStream::eos){
		if(optCodeMap.count(opt)){
			SCIInstruction ins(optCodeMap[opt],-1,-1,-1);
			return ins;
		}
		else{
			cout<<"错误的指令"<<opt;
			Sleep(10000); 
			exit(-1);
		}
	}
	arg="";
	while(!(isalnum(ch)||ch==ICStream::eos||ch=='"')){
		ch=stream->read();
	}
	while(isalnum(ch)||ch==' '||ch=='"'){
		arg+=ch;
		ch=stream->read();
	}
	if(isNumber(arg)){
		Value value(toNumber(arg));
		arg1=program->addValue(value);
	}
	else if(isDecimal(arg)){
		Value value(toDecimal(arg));
		arg1=program->addValue(value);
	}
	else if(isString(arg)){
		Value value(toString(arg));
		arg1=program->addValue(value);
	}
	else if(CFunctionMap.count(arg)){
		Value value(arg);
		value.setType(Value::TYPE_FUNCTION);
		arg1=program->addValue(value);
	}
	if(ch=='\n'||ch=='\r'||ch==ICStream::eos||ch=='"'){
		if(optCodeMap.count(opt)){
			SCIInstruction ins(optCodeMap[opt],arg1,-1,-1);
			return ins;
		}
		else{
			cout<<"错误的指令"<<opt;
			Sleep(10000);
			exit(-1);
		}
	}
	arg="";
	while(!(isalnum(ch)||ch==ICStream::eos||ch=='"')){
		ch=stream->read();
	}
	while(isalnum(ch)||ch==' '||ch=='"'){
		arg+=ch;
		ch=stream->read();
	}
	if(isNumber(arg)){
		Value value(toNumber(arg));
		arg2=program->addValue(value);
	}
	else if(isDecimal(arg)){
		Value value(toDecimal(arg));
		arg2=program->addValue(value);
	}
	else if(isString(arg)){
		Value value(toString(arg));
		arg2=program->addValue(value);
	}
	else if(CFunctionMap.count(arg)){
		Value value(arg);
		value.setType(Value::TYPE_FUNCTION);
		arg2=program->addValue(value);
	}
	if(ch=='\n'||ch=='\r'||ch==ICStream::eos||ch=='"'){
		if(optCodeMap.count(opt)){
			SCIInstruction ins(optCodeMap[opt],arg1,arg2,-1);
			return ins;
		}
		else{
			cout<<"错误的指令"<<opt;
			Sleep(10000);
			exit(-1);
		}
	}
	arg="";
	while(!(isalnum(ch)||ch==ICStream::eos||ch=='"')){
		ch=stream->read();
	}
	while(isalnum(ch)||ch==' '||ch=='"'){
		arg+=ch;
		ch=stream->read();
	}
	if(isNumber(arg)){
		Value value(toNumber(arg));
		arg3=program->addValue(value);
	}
	else if(isDecimal(arg)){
		Value value(toDecimal(arg));
		arg3=program->addValue(value);
	}
	else if(isString(arg)){
		Value value(toString(arg));
		arg3=program->addValue(value);
	}
	else if(CFunctionMap.count(arg)){
		Value value(arg);
		value.setType(Value::TYPE_FUNCTION);
		arg3=program->addValue(value);
	}
	if(ch=='\n'||ch=='\r'||ch==ICStream::eos){
		if(optCodeMap.count(opt)){
			SCIInstruction ins(optCodeMap[opt],arg1,arg2,arg3);
			return ins;
		}
		else{
			cout<<"错误的指令"<<opt;
			Sleep(10000);
			exit(-1);
		}
	}
	if(optCodeMap.count(opt)){
		SCIInstruction ins(optCodeMap[opt],arg1,arg2,arg3);
		return ins;
	}
	else{
		cout<<"错误的指令"<<opt;
		Sleep(10000);
		exit(-1);
	}
}

int Executer::execute()
{
	while(true){
		SCIInstruction ins = getSource();
		switch(ins.opt){
			case SCIInstruction::EXIT:
			{
				Value vexit=program->get(ins.arg1);
				program->pop();
				return vexit.getNumber();
			}
			case SCIInstruction::PUSH:
			{
				Value vpush=program->get(ins.arg1);
				cout<<ins.arg1;
				program->pop();
				program->addValue(vpush);
				break;
			}
			case SCIInstruction::CALL:
			{
				if(CFunctionMap.count(program->get(ins.arg1).getFunction())){
					string fun=program->get(ins.arg1).getFunction();
					program->pop();
					CFunctionMap[fun](program);
				}
				else{
					//TODO:添加自定义函数 
				}
				break;
			}
		}
	}
}
