#include "token.h"

Token::Token() : type(INVAILD),line(0)
{
	
}

Token::Token(kind typeIn,int lineIn) : type(typeIn),line(lineIn)  
{
	
}

Lexer::Lexer(IStream* streamIn) : 
	curchar(' '),line(1),Current(current),Next(next),Source(source),stream(streamIn) 
{
	
}

Lexer::~Lexer()
{
	
}

inline void Lexer::getChar()
{
	this->curchar=this->stream->read(); 
}

inline void Lexer::incLine()
{
	this->line++; 
}

inline bool Lexer::isLine(int c)
{
	return c=='\n'||c=='\r';
}

Token Lexer::getToken()
{
	source="";
	while(true){
		getChar();
		switch(curchar){
			default:
			break; 
		}
	}
}
 
void Lexer::comment()
{
	while(!isline(curchar)){
		getChar();
	}
}

Token Lexer::identifier()
{
	
}

Token Lexer::number()
{
	while(isalnum(curchar)){
		getChar();
	}
	//if(curchar!=' '&&curchar!=';'&&curchar!='+')
	Token token(Token::NUMBER,this->line);
}

Token Lexer::decimal()
{
	int value=0;
	double x=0;
	int decl=0;
	bool isDecimal=false;
	while(isalnum(curchar)||curchar=='.'){
		if(curchar=='.'){
			if(isDecimal){
				errorUnexpected("数字");
			}
			isDecimal=true;
			continue;
		}
		if(!isDecimal)
			value=value*10+curchar-'0';
		else
		{
			x=x*10+curchar-'0';
			decl++;
		}
		getChar();
	}
	return 
}

Token Lexer::stringLiteral()
{
	
}

void Lexer::error(const char* msg,...)
{
	va_list args;
	va_start(args,msg);
	vfprintf(stderr,msg,args);
	va_end(args);
	ErrorExit();
}

void Lexer::errorUnexpected(char expected)
{
	error("行%d: 期望'%c'(ASCII:%d),但读到了'%c'(ASCII:%d)!",
		this->line,expected,expected,this->curchar,this->curchar); 
}

void Lexer::errorUnexpected(string expected)
{
	error("行%d: '%c'(ASCII:%d)不属于%s的类别！",
		this->line,this->curchar,this->curchar,expected.c_str());
}

void Lexer::errorInvalid()
{
	error("行%d: 错误的字符'%c'(ASCII:%d)!",
		this->line,this->curchar,this->curchar);
}

