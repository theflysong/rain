#ifndef __TOKEN__
#define __TOKEN__

#include "head.h"

/*
	������
	�﷨�����ĵ�λ 
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
	�﷨���� 
*/
class Lexer
{
protected:
	Token current; //��ǰ����
	Token next; //��һ������
	string source; //Դ�� 
	IStream* stream; //������ 
	map<string,Token::kind> words;
	char curchar;
	int line;
	/*��ȡһ���ַ�*/ 
	inline void getChar();
	/*ת����һ��*/
	inline void incLine();
	/*�Ƿ�Ϊ���з�*/
	inline bool isLine(int c);
	/*���дʷ�����*/
	Token getToken(); 
	/*ע�ʹ���*/
	void comment();
	/*��ʶ��\�ؼ���*/
	Token identifier();
	/*����*/
	Token number();
	/*С��*/
	Token decimal();
	/*�ַ���*/
	Token stringLiteral();
	/*����*/
	void error(const char* msg,...);
	/*��Ԥ���ַ�����*/
	void errorUnexpected(char expected);
	/*��Ԥ����𱨴�*/
	void errorUnexpected(const char* expected);
	/*�Ƿ��ַ�����*/
	void errorInvalid();
public:
	/*
		ֻ������ 
	*/
	const Token &Current; //��ǰ���� 
	const Token &Next; //��һ������ 
	const string &Source; //Դ�� 
	/* ���캯�� */
	Lexer(IStream* stream);
	/* �������� */
	virtual ~Lexer();
	/* ��ȡ��һ������ */
	void Read();
	/* �鿴��һ������ */
	void Peek();
};

#endif


