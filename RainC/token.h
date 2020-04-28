#ifndef __TOKEN__
#define __TOKEN__

#include "head.h"

/*
	单词类
	语法分析的单位 
*/
class Token
{
public:
	enum kind
	{
		EOS = -1,
		INVAILD = 0,
		ID=32,
		NUMBER,
		STRING,
		DECIMAL 
	};
private: 
	kind type;
	int line;
public:
	Token();
	Token(kind type,int line);
};

/*	
	语法分析 
*/
class Lexer
{
protected:
	Token current; //当前单词
	Token next; //下一个单词
	string source; //源码 
	IStream* stream; //单词流 
	map<string,Token::kind> words;
	char curchar;
	int line;
	/*获取一个字符*/ 
	inline void getChar();
	/*转到下一行*/
	inline void incLine();
	/*是否为换行符*/
	inline bool isLine(int c);
	/*进行词法分析*/
	Token getToken(); 
	/*注释处理*/
	void comment();
	/*标识符\关键字*/
	Token identifier();
	/*整数*/
	Token number();
	/*小数*/
	Token decimal();
	/*字符串*/
	Token stringLiteral();
	/*报错*/
	void error(const char* msg,...);
	/*非预期字符报错*/
	void errorUnexpected(char expected);
	/*非预期类别报错*/
	void errorUnexpected(const char* expected);
	/*非法字符报错*/
	void errorInvalid();
public:
	/*
		只读属性 
	*/
	const Token &Current; //当前单词 
	const Token &Next; //下一个单词 
	const string &Source; //源码 
	/* 构造函数 */
	Lexer(IStream* stream);
	/* 析构函数 */
	virtual ~Lexer();
	/* 读取下一个单词 */
	void Read();
	/* 查看下一个单词 */
	void Peek();
};

#endif


