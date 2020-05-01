#include "Execute.h"
#include "CFunctions.h"

#define error(err) cerr<<"[Error]:"<<err;

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
	CFunctionMap["sleep"]=sleep;
}

inline bool isNumber(string str)
{
	for(int i=0;i<str.length();i++){
		if(str[i]=='-'||str[i]=='+'){
			if(i==0)
				continue;
			return false;
		}
		if(!isdigit(str[i]))
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
	bool b=false;
	for(int i=0;i<str.length();i++){
		if(str[i]=='-'||str[i]=='+'){
			if(i==0)
				continue;
			return false;
		}
		if(!(isdigit(str[i])||str[i]=='.'))
			return false;
		if(str[i]=='.')
			if(b)
				return false;
			else
				b=true;
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

inline char getArgs(ICStream* stream,string &str){
	char ch=stream->read();
	while(!(isalnum(ch)||ch==ICStream::eos||ch=='"'||ch=='-'||ch=='+')){
		ch=stream->read();
	}
	if(ch=='"'){
		str+=ch;
		while(true){
			ch=stream->read();
			if(ch=='"'&&str[str.length()-1]!='\\'){
				break;
			}
			str+=ch;
		}
		str+='"';
		ch=stream->read();
		while(ch!='\n'&&ch!='\r'){
			stream->read();
		}
		return ch;
	} 
	while(isalnum(ch)||ch==' '||ch=='.'||ch=='-'||ch=='+'){
		str+=ch;
		ch=stream->read();
	}
	return ch;
}

inline char getOpt(ICStream* stream,string &str){
	char ch=stream->read();
	while(!(isalnum(ch)||ch==ICStream::eos||ch=='\n'||ch=='\r')){
		ch=stream->read();
	}
	while(isalnum(ch)){
		str+=ch;
		ch=stream->read();
	}
	return ch;
}

inline char LexerCode(ICStream* stream,int &arg1){
	string arg="";
	char ch=getArgs(stream,arg);
	if(isNumber(arg)){
		arg1=program->addValue(new Value(toNumber(arg)));
	}
	else if(isDecimal(arg)){
		arg1=program->addValue(new Value(toDecimal(arg)));
	}
	else if(isString(arg)){
		arg1=program->addValue(new Value(toString(arg),Value::TYPE_STRING));
	}
	else if(CFunctionMap.count(arg)){
		arg1=program->addValue(new Value(arg,Value::TYPE_FUNCTION));
	}
	return ch;
}


SCIInstruction Executer::getSource()
{
	string opt="";
	int arg1,arg2,arg3;
	string arg="";
	char ch=getOpt(this->stream,opt);
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
	ch = LexerCode(this->stream,arg1);
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
	ch = LexerCode(this->stream,arg1);
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
	ch = LexerCode(this->stream,arg1);
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
				int state=program->get(ins.arg1)->getNumber();
				program->remove(ins.arg1);
				return state;
			}
			case SCIInstruction::PUSH:
			{
				break;
			}
			case SCIInstruction::CALL:
			{
				Value* v=program->get(ins.arg1);
				if(v->getType()!=Value::TYPE_FUNCTION){
					string e="错误的类型!值类型应为Function,但类型为"+Value::toString(v->getType());
					error(e); 
					return -1; 
				} 
				if(CFunctionMap.count(v->getFunction())){
					string str=v->getFunction();
					program->remove(ins.arg1);
					Value* value = CFunctionMap[str](program);
					if(value!=NULL)
						program->addValue(value);
					break;
				}
				else{
					//TODO:添加自定义函数 
				}
				program->remove(ins.arg1);
				break;
			}
		}
	}
}
