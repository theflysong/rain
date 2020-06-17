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
	optCodeMap["new"]=SCIInstruction::NEW;
	optCodeMap["del"]=SCIInstruction::DEL;
	optCodeMap["jpt"]=SCIInstruction::JPT;
	optCodeMap["jpf"]=SCIInstruction::JPF;
	optCodeMap["cmp"]=SCIInstruction::CMP;
	optCodeMap["add"]=SCIInstruction::ADD; 
	optCodeMap["sub"]=SCIInstruction::SUB;
	optCodeMap["mul"]=SCIInstruction::MUL;
	optCodeMap["dev"]=SCIInstruction::DEV;
	optCodeMap["mod"]=SCIInstruction::MOD; 
	optCodeMap["inc"]=SCIInstruction::INC; 
	optCodeMap["dec"]=SCIInstruction::DEC; 
	optCodeMap["set"]=SCIInstruction::SET;
	
	/*CFunction*/
	CFunctionMap["print"]=print; 
	CFunctionMap["sleep"]=sleep;
	
	/*TYPES*/
	program->typeMap["number"]=Value::TYPE_NUMBER;
	program->typeMap["string"]=Value::TYPE_STRING;
	program->typeMap["decimal"]=Value::TYPE_DECIMAL;
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
	else if(program->hasVariable(arg)){
		arg1=program->addValue(new Value(arg,Value::TYPE_ID));
	}
	else if(program->typeMap.count(arg)){
		arg1=program->addValue(new Value(program->typeMap[arg],arg));
	} 
	return ch;
}

int LexerDef(ICStream* stream){
	string arg="";
	char ch=getArgs(stream,arg);
	return program->addValue(new Value(arg,Value::TYPE_ID));
}

SCIInstruction Executer::getSource()
{
	string opt="";
	int arg1,arg2,arg3;
	string arg="";
	char ch=getOpt(this->stream,opt);
	if(opt=="def"){
		arg1=LexerDef(this->stream);
		SCIInstruction ins(SCIInstruction::DEF,arg1,-1,-1);
		return ins;
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
	ch = LexerCode(this->stream,arg1);
	if(ch=='\n'||ch=='\r'||ch==ICStream::eos){
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
	ch = LexerCode(this->stream,arg2);
	if(ch=='\n'||ch=='\r'||ch==ICStream::eos){
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
	ch = LexerCode(this->stream,arg3);
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
			case SCIInstruction::NEW:
			{
				string name = program->get(ins.arg1)->getID();
				program->remove(ins.arg1);
				if(!program->hasVariable(name)){
					error("没有变量"<<name);
					ErrorExit();
				}
				program->setVariable(name,new Value(program->get(ins.arg2)->getClass()));
				break;			
			}
			case SCIInstruction::DEF:
			{
				string name = program->get(ins.arg1)->getID();
				program->remove(ins.arg1);
				program->addVariable(name,"");
				break;
			}
			case SCIInstruction::SET:
			{
				Value* v1 = program->get(ins.arg2);
				if(v1->getType()==Value::TYPE_ID){
					v1=program->getVariable(v1->getID());
				}
				string ID = program->get(ins.arg1)->getID();
				program->remove(ins.arg1);
				
				if(!program->hasVariable(ID)){
					error("没有变量"<<ID);
					ErrorExit();
				}
				Value* v2 = program->getVariable(ID);
				if(v2==(Value*)NULL){
					error("Null!");
				}
				switch(v1->getType()){
					case Value::TYPE_ID: v2->setID(v1->getID());break;
					case Value::TYPE_FUNCTION: v2->setFunction(v1->getFunction());break;
					case Value::TYPE_NUMBER: v2->setNumber(v1->getNumber());break;
					case Value::TYPE_DECIMAL: v2->setDecimal(v1->getDecimal());break;
					case Value::TYPE_STRING: v2->setStr(v1->getStr());break;
					default: break;
				}
				program->remove(ins.arg2);
				break;
			}
		}
	}
}
